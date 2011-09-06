<?php
// $Id: ipaper.admin.inc,v 1.1.2.1 2009/10/08 05:34:09 rares Exp $
// $Name: DRUPAL-6--1-1 $
/*
 * @file
 * iPaper administration page
 */


/**
 * Ipaper Configuration Form
 */

function ipaper_config_form() {
  $form['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('Scribd API settings'),
    '#description' => t('These values are necessary for you to be able to upload iPapers. Set up a scribd API account at <a href="http://www.scribd.com/platform/start">http://www.scribd.com/platform/start</a>.'),
  );
  $form['api']['scribd_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API key'),
    '#default_value' =>  variable_get('scribd_api_key', ''),
    '#description' => t('The scribd.com API key for your website.'),
  );
  $form['api']['scribd_secret_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret key'),
    '#default_value'   => variable_get('scribd_secret_key', ''),
    '#description' => t('The scribd.com secret key for your website.  This is optional but provides added security. Enable "Require API signature" in your <a href="http://www.scribd.com/people/account">Scribd account</a>to prevent third parties from using just the API key to post requests.'),
  );

  $form['nodes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ipaper cusomizations'),
    '#description' => t('These settings affect the options available when iPapers are created/edited'),
  );
  $form['nodes']['ipaper_default_private'] = array(
    '#type' => 'select',
    '#title' => t('Default visibility setting'),
    '#options' => ipaper_private_options(),
    '#default_value' =>  variable_get('ipaper_default_private', DEFAULT_PRIVATE),
    '#description' => t('Private documents are only available through your website. Public documents are also available on scribd.com and are indexed by search engines.'),
  );
  $form['nodes']['ipaper_choose_private'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show visibility option?'),
    '#default_value' =>  variable_get('ipaper_choose_private', 1),
    '#description' => t('Allow users to choose whether their documents are private or public?'),
  );
  $form['nodes']['ipaper_default_license'] = array(
    '#type' => 'select',
    '#title' => t('Licensing on scribd.com'),
    '#options' => ipaper_license_options(),
    '#default_value' =>  variable_get('ipaper_default_license', DEFAULT_LICENSE),
    '#description' => t('The license under which documents are released. The license is shown on scribd.com.'),
  );
  $form['nodes']['ipaper_choose_license'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show license option?'),
    '#default_value' =>  variable_get('ipaper_choose_license', 1),
    '#description' => t('Allow users to choose the license?'),
  );
  
  //Restrict use of documents outside your Drupal site. For more information, see http://www.scribd.com/publisher/ipaper_secure
  $form['nodes']['ipaper_default_secure'] = array(
    '#type' => 'select',
    '#title' => t('Upload iPaper documents as secure? '),
    '#options' => ipaper_secure_options(),
    '#default_value' =>  variable_get('ipaper_default_secure', DEFAULT_SECURE),
    '#description' => t('Should new ipapers be secure? Secure uploads cannot be embedded on other sites. Note that this is set permanently for each document when it is first uploaded. Important: You must paste your Scribd Secret key on this page for this feature to work.'),
  );
  $form['nodes']['ipaper_choose_secure'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show secure option'),
    '#default_value' =>  variable_get('ipaper_choose_secure', 0),
    '#description' => t('Allow users to choose whether their documents are secure or not? '),
  );


  $form['nodeview'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node view'),
    '#description' => t('Control the display of iPapers as full nodes.'),
  );
  $form['nodeview']['ipaper_download_format'] = array(
    '#type' => 'select',
    '#title' => t('Download format'),
    '#options' => array('pdf' => 'PDF', 'original' => 'Original format', 'txt' => "Plain text"),
    '#default_value' =>  variable_get('ipaper_download_format', 'pdf'),
    '#description' => t('This is the format that users with the "download ipapers" permissions will download the documents in.'),
  );
  $form['nodeview']['ipaper_show_scribd_link'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show link to Scribd document.'),
    '#default_value' =>  variable_get('ipaper_show_scribd_link', 0),
    '#description' => t('If checked, a link to view the document on scribd.com will be displayed.'),
  );
  $form['nodeview']['ipaper_show_full_text'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include full text on pages.'),
    '#default_value' =>  variable_get('ipaper_show_full_text', 1),
    '#description' => t('If checked, the plain text of the documents will be included on the pages in < noscript > tags (visible only to users that cannot see the iPaper viewer because Javascript is disabled). This is necessary if you want search engines to be able to index your content. However, it allows visitors to extract the text from the source of the page.'),
  );

  $form['teaserview'] = array(
    '#type' => 'fieldset',
    '#title' => t('Teaser view'),
    '#description' => t('Teaser view customizations.'),
  );
  $form['teaserview']['ipaper_thumbnail_size'] = array(
    '#type' => 'select',
    '#title' => t('Thumbnail size (height)'),
    '#options' => array(0 => 'none', 100 => '100px', 140 => '140px', 170 => '170px', 220 => '220px', 270 => '270px'),
    '#default_value' =>  variable_get('ipaper_thumbnail_size', 140),
    '#description' => t("This setting affects whether the module downloads large or small thumbnails to display with your iPaper nodes. If you change this after you have created documents, you should rebuild your thumbnail cache. Note that for any values other than 100px and 220px, scaling is done in the user's browser. Support for enlarged thumbnails is experimental, so if thumbnails are not appearing, choose the 100px option, save this form and then rebuild the thumbnail cache."),
  );
  $form['teaserview']['clear'] = array(
    '#type' => 'submit',
    '#value' => t('Rebuild thumbnail cache'),
    '#submit' => array('ipaper_flush_thumb_cache_submit'),
    '#description' => t('Removes and re-downloads thumbnails stored in the ipaper_thumbs/ folder.'),
  );

  $form['admin'] = array(
    '#type' => 'fieldset',
    '#title' => t('Administrator settings'),
    '#description' => t('Control the backend of the module.'),
  );
  $form['admin']['ipaper_extraJS'] = array(
    '#type' => 'textarea',
    '#title' => t('Additional iPaper Javascript API code'),
    '#default_value' =>  variable_get('ipaper_extraJS', ''),
    '#description' => t('This code will be included in a < script > block together when the iPaper viewer is themed. For example:<br> scribd_doc.addParam("mode", "book"); scribd_doc.addParam("hide_full_screen_button", true);<br> To see what parameters are available, refer to <a href="http://www.scribd.com/developers/api?method_name=Javascript+API#parameters">the Scribd API documentation</a>. <strong>Use with caution:</strong> entering incorrect Javascript will prevent iPapers from being displayed.'),
  );
  $form['admin']['ipaper_extradocsettings'] = array(
    '#type' => 'textarea',
    '#title' => t('Additional document properties'),
    '#default_value' =>  variable_get('ipaper_extradocsettings', ''),
    '#description' => t('<strong>Use with extreme caution</strong>, as these parameters will be included in each API request when a node is created or updated (docs.changeSettings). Put each parameter-value combination on a new line, like:<br>disable_print=1<br> Entering incorrect parameters will limit your ability to make API requests. For more examples, see <a href="http://www.scribd.com/developers/api?method_name=docs.changeSettings">the Scribd API documentation</a>. Do not include access, license and secure parameters here, as they are already handled by the module. If you have made changes in the document parameters that you would like to apply to all the documents on this site, you can run a bulk update on all of them. Save this admin form to save your new parameters changes, then click the button below to run the update.'),
  );
  $form['admin']['ipaper_bulk_assign_params'] = array(
    '#type' => 'submit',
    '#value' => t('Assign these parameters to all existing nodes'),
    '#submit' => array('ipaper_bulk_assign_params_submit'),
    '#description' => t(''),
  );
  $form['admin']['ipaper_request_framework'] = array(
    '#type' => 'select',
    '#title' => t('HTTP Request framework'),
    '#options' => array(PLATFORM_EITHER => "Either method (default, recommended)", PLATFORM_CURL => 'CURL', PLATFORM_FOPEN => 'fopen (drupal_http_request)'),
    '#default_value' =>  variable_get('ipaper_request_framework', PLATFORM_EITHER),
    '#description' => t('If you are having problems with the default setting, you can try using fopen.'),
  );
  $form['admin']['ipaper_log_requests'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log all API requests to the event log'),
    '#default_value' =>  variable_get('ipaper_log_requests', 0),
    '#description' => t('Allows administrators to diagnose or track communication through the Scribd API.'),
  );
 
  return system_settings_form($form);
}


/**
 * Rebuild thumbnail cache
 */
function ipaper_flush_thumb_cache_submit(&$form_state, $form) {
  file_scan_directory(file_directory_path() .'/ipaper_thumbs', '.*', array('.', '..', 'CVS'), 'file_delete');
  $result = db_query("SELECT doc_id FROM {ipaper} WHERE doc_id<>0");
  $scribd = ipaper_scribd_init();
  $count = 0;
  while ($row = db_fetch_object($result)) {
    $saved = _ipaper_save_thumb($row->doc_id, $scribd);
    if ($saved) $count += 1;
  }
  drupal_set_message("Thumbnails cleared, $count new thumbnails saved.");
}

/**
 * Bulk assign API parameters
 */
function ipaper_bulk_assign_params_submit(&$form_state, $form) {
  $result = db_query("SELECT doc_id FROM {ipaper} WHERE doc_id<>0");
  $scribd = ipaper_scribd_init();
  $count = 0;
  while ($row = db_fetch_object($result)) {
    $doc_ids[] = $row->doc_id;
    $count += 1;
  }
  
  $doc_ids_CSV = implode(',', $doc_ids);
  //additional parameters from admin screen
  $params = ipaper_additionalAPIparams();

  $result = $scribd->changeSettings($doc_ids_CSV, $params);
  drupal_set_message("$count documents processed.");
  if (!$result) ipaper_report_error();
}

