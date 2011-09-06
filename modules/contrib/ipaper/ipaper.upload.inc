<?php
// $Id: ipaper.upload.inc,v 1.1.2.1 2009/10/08 05:34:32 rares Exp $
// $Name: DRUPAL-6--1-1 $
/*
 * @file
 * iPaper upload functions and API calls to update document properties, get thumbnails and full text etc.
 */

/**
 * Menu callback: ipaper_transfer
 *  This function is called each time an ipaper node is created/updated and has the role of
 * synchronizing the document on the scribd server with the Drupal node.
 *  Note that these operations happen at a menu callback page rather than in _update or _insert because:
 * 1. within _update and _insert the attachments have not been saved
 * 2. nodes should be saved regardless of whether the 'transfer' succeeds (a timeout or error for the
 *    API at scribd.com should not affect the node update
 * 3. it helps to display a progress bar while the file is transferred to scribd.com, since this could take a while
 */

function ipaper_transfer($node) {

  if ($node->type != 'ipaper') {drupal_access_denied(); return;}
  $files = $node->files;
  if ($files) $file = end($files);
  //returns the most recent upload for this node

  if (!($file)) {
    drupal_goto("node/$node->nid");
    return;
  }

  if ($node->fid == $file->fid && $node->doc_id) {
    //The current version is already on scribd.

    //send the settings for this node to Scribd using docs.changeSettings
    ipaper_saveAPIparams($node);
    
    //refresh the thumbnail, just in case a pdf or word icon was given by scribd initially
    @file_delete(_ipaper_get_thumb_path($node->doc_id));
    _ipaper_save_thumb($node->doc_id);

    drupal_goto("node/$node->nid");
    return;
  }

  //the file on scribd needs to be updated/created set the stage for a file upload
  $dest = url("ipaper_upload/$node->nid");
  drupal_set_html_head('<meta http-equiv="Refresh" content="0;URL='. $dest .'">');
  $text = theme('progress_bar', NULL, t('Preparing document...'));
  $text .= t('This can take a while, depending on the size of your upload.');
  return $text;

}

/**
 * Menu callback: ipaper_upload
 * The user is sent to this page from ipaper_transfer if there is a new file that needs to be uploaded to Scribd
 */
 
function ipaper_upload($node) {

  $starttime = time();
  if ($node->type != 'ipaper') {drupal_access_denied(); return;}
  $files = $node->files;
  if ($files) $file = end($files);
  //returns the most recent upload for this node

  $scribd = ipaper_scribd_init();

  $params = array();
  $params['file'] = "@". $file->filepath;
  $params['doc_type'] = NULL;
  $params['access'] = $node->private;
  if($node->secure){
    $params['secure'] = 1;
    $params['secure_document'] = 1;
  }

  //adds a new revision to an existing scribd document, if it exists
  if ($node->doc_id) {
    $params['rev_id'] = $node->doc_id;
  }

  $data = $scribd->upload($params);

  if ($data) {
    $res=$scribd->getdocresult();
    $node->fid = $file->fid;
    //explicit conversion is necessary, see http://drupal.org/node/199337
    $node->doc_id = (string) $res->doc_id;
    $node->access_key = (string) $res->access_key;
    $node->secret_password = (string) $res->secret_password;

    //save doc_id, access_key, secret_password to Drupal database
    _ipaper_dbupdate_params($node);

    if ($rev_id) {
      drupal_set_message(t('A new version of your document has been uploaded. It may take a few minutes until the most recent version is displayed.'));
      file_delete(_ipaper_get_thumb_path($node->doc_id));
    }

    //send the settings for this node to Scribd using docs.changeSettings
    ipaper_saveAPIparams($node);

    $stat = $scribd->getConversionStatus($node->doc_id);

    if ($stat == "ERROR") {
      drupal_set_message(t("Your document could not be successfully converted to an iPaper. See the message in the document display for more information"), 'error');
      watchdog("ipaper", t("Scribd failed conversion for document") . $node->title, NULL, WATCHDOG_ERROR, l($node->title, "node/$node->nid"));
      drupal_goto("node/$node->nid");
      return;
    }

  }
  else ipaper_report_error();

  drupal_goto("node/$node->nid");

}

/*
 * Called by ipaper_transfer and ipaper_upload to send parameters that were set in Drupal to Scribd
 */

function ipaper_saveAPIparams($node){

    $scribd = ipaper_scribd_init();
    global $base_url;
    
    $params = array();
    $params['title'] = $node->title;
    //$params['description'] = $node->body;
    $params['access'] = $node->private;
    //if license is unspecified, don't send anything to scribd
    $params['license'] = ($node->license=='ns') ? $node->license : NULL;
    //setting the secure property is currently supported only in the upload phase
    //$params['secure'] = $node->secure;
    //$params['tags'] = '';
    $params['link_back_url'] = $base_url ."/node/$node->nid";
    
    //additional parameters from admin screen
    $params = array_merge($params, ipaper_additionalAPIparams());

    $result = $scribd->changeSettings($node->doc_id, $params);
    if (!$result) ipaper_report_error();

}

/**
 * Creates an array of the parameters that need to be assigned to all nodes
 */
 
function ipaper_additionalAPIparams(){

  $extraparams = variable_get('ipaper_extradocsettings', '');
  $params = array();
  $pattern = "/([0-9_A-z]*)=([0-9_A-z ,]*)/";
  preg_match_all($pattern, $extraparams, $results);
  $output = $text;
  foreach($results[0] as $rid=>$result){
    $pname = $results[1][$rid];
    $pvalue = $results[2][$rid];
    $params[$pname] = $pvalue;
  }
  return $params;

}

/*
 * Redirects users to download the iPaper from scribd.com
 */

function ipaper_download($node) {

  $doc_id = $node->doc_id;
  if ($doc_id) {
    $scribd = ipaper_scribd_init();
    $format = variable_get('ipaper_download_format', 'pdf');
    $link = $scribd->getDownloadURL($node->doc_id, $format);
    $link = trim($link);
    if ($link) {
      drupal_goto($link);
      return;
    }
  }
  drupal_set_message(t("Not an iPaper or the download link is not available"), 'error');
  drupal_goto("node/$nid");

}

/**
 * Cache thumbnails from scribd server.
 */
function _ipaper_save_thumb($doc_id) {

  $size = variable_get('ipaper_thumbnail_size', 170);
  if ($size == 0) return;

  $scribd = ipaper_scribd_init();
  //If conversion is not complete, we will not get a good thumbnail
  $stat = $scribd->getConversionStatus($doc_id);
  if ($stat != 'DONE') return;

  $result = $scribd->getSettings($doc_id);  
  //Trim is VERY important, cURL will break if this is not cleaned
  $source = trim($result['thumbnail_url']);

  if ($size > 100) {
    //Try to guess the URL for a larger version of the thumbnail
    if(strpos($source, 'thumbnail'))
      $largeurl = str_replace('thumbnail.jp', 'thumbnail_large.jp', $source);
    else
      $largeurl = str_replace('thumb', 'large', $source);
    $request = _ipaper_request($largeurl);
  }
  //for the smaller version of the thumbnail, or if the URL for the larger version was incorrect
  if(!$request || strpos($request, 'Error')){
    $request = _ipaper_request($source);
  }
  $destination = _ipaper_get_thumb_path($doc_id);
  if ($request) {
    // Check that the files directory is writable
    if (file_check_directory(dirname($destination), FILE_CREATE_DIRECTORY)) {
      $result = file_save_data($request, $destination, FILE_EXISTS_REPLACE);
      if ($result)
        return TRUE;
    }
    else{
      watchdog('ipaper', "Could not write thumbnail for doc_id %doc_id", array('%doc_id' => $doc_id), WATCHDOG_ERROR);
    }
  }//if $request
  return FALSE;
}

/**
 * Handles all HTTP requests for this module
 * Provides for increased compatibility by sending requests either through CURL or fsockopen(drupal_http_request)
 */
function _ipaper_request($request_url, $params = NULL, $method = 'GET') {

  if (variable_get('ipaper_log_requests', 0) && $params) {
    $apimethod = $params['method'];
    $doc_id = $params['doc_id'] ? $params['doc_id'] : $params['doc_ids'];
    //remove these important parameters so that they are not included in the log messages
    $logparams = $params;
    if($logparams['api_key']) $logparams['api_key']='xxx';
    if($logparams['api_sig']) $logparams['api_sig']='xxx';
    $link = $request_url . ipaper_list_params($logparams);
    watchdog('ipaper', "Action: %apimethod, Document ID: %doc_id \n URL: %link", array('%apimethod' => $apimethod, '%doc_id' => $doc_id, '%link' => $link), WATCHDOG_NOTICE);
  }

  $platform = variable_get('ipaper_request_framework', PLATFORM_EITHER);
  if ($platform == PLATFORM_EITHER){
    if(function_exists("curl_init"))
      $platform = PLATFORM_CURL;
    else
      $platform = PLATFORM_FOPEN;
  }
  
  if ($platform == PLATFORM_CURL) {
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    if ($method == 'POST') {
      curl_setopt($ch, CURLOPT_POST, 1 );
      curl_setopt($ch, CURLOPT_POSTFIELDS, $params);
      curl_setopt($ch, CURLOPT_URL, $request_url);
    }
    else {
      curl_setopt($ch, CURLOPT_URL, $request_url . ipaper_list_params($params));
    }    
    $data = curl_exec($ch);
    if (curl_errno($ch)) {
      $link = $request_url . ipaper_list_params($params);
      drupal_set_message(t("Request to Scribd.com failed. See the event log for more details."), 'error');
      watchdog("ipaper", "Request failed (CURL) - %err - %link", array('%err' => curl_error($ch), '%link' => $link), WATCHDOG_ERROR);
    }
    curl_close($ch);
    return $data;
  }
  else{
    $headers = array();
    $data = NULL;
    if ($method == "POST") {
      require_once drupal_get_path('module', 'ipaper') .'/multipart.inc';
      $boundary = 'A0sFSD';
      $headers = array("Content-Type" => "multipart/form-data; boundary=$boundary");
      $data = multipart_encode($boundary, $params);
    $request = drupal_http_request($request_url, $headers, $method, $data);
    }
    else {
      $request = drupal_http_request($request_url . ipaper_list_params($params), $headers, $method, $data);
    }
    if ($request->error) {
      $link = $request_url . ipaper_list_params($params);
      drupal_set_message(t("Request to Scribd.com failed. See the event log for more details."), 'error');
      watchdog("ipaper", t("Request failed (FOPEN) - %err - %link"), array('%err' => $request->error, '%link' => $link), WATCHDOG_ERROR);
      if ($request->code < 0) {
        watchdog("ipaper", t("fsockopen might not be supported on your server. CURL must be installed or fsockopen enabled in order for the ipaper module to work"), NULL, WATCHDOG_ERROR);
      }
    }
    return $request->data;
  }

}

/**
 * Ipaper Configuration Form
 * This is essentially an replacement for http_build_query, which was not used because it requires PHP5
 */
 
function ipaper_list_params($params) {

  if ($params == NULL) return;
  $output = '';
  foreach ($params as $key => $value)
    $output .= "&$key=". urlencode($value);
  return $output;
}
