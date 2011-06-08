<?php

/**
 * @file
 * This file contains the functions for the admin interface for yr_verdata.
 */

/**
 * Administrative settings for yr_verdata.
 *
 * @return
 * Returns a form array to be processed by drupal_get_form().
 */
function yr_verdata_settings($form) {

  $form = array();

  $form['yc'] = array(
    '#type' => 'fieldset',
    '#title' => t('Forecast customization'),
    '#description' => t('Choose the default formats and unit types you want to display the forecasts in.'),
    '#collapsible' => TRUE,
  );
  // Set up dates. This is more awkward in D6 than D7, so w'ell have to make do with what we can.
/*  $available_date_types = array('small', 'medium', 'large');
  $date_options = array();
  foreach ($available_date_types as $type) {
    $date_options[$type] = format_date(time(), $type);
  }
  $form['yc']['yr_verdata_date_format'] = array(
    '#type' => 'select',
    '#title' => t('Date format'),
    '#options' => $date_options,
    '#default_value' => variable_get('yr_verdata_date_format', 'small'),
    '#description' => t('These formats can be managed at !datetime.', array('!datetime' => l('admin/settings/date-time', 'admin/settings/date-time'))),
  );*/
  $form['yc']['yr_verdata_temp_unit'] = array(
    '#type' => 'select',
    '#title' => t('Temperature unit'),
    '#options' => array('celsius' => t('Celsius'), 'fahrenheit' => t('Fahrenheit'), 'kelvin' => t('Kelvin')),
    '#default_value' => variable_get('yr_verdata_temp_unit', 'celsius'),
  );
  $form['yc']['yr_verdata_press_unit'] = array(
    '#type' => 'select',
    '#title' => t('Pressure unit'),
    '#options' => drupal_map_assoc(array('hPa', 'bar', 'psi', 'inHg', 'torr')),
    '#default_value' => variable_get('yr_verdata_press_unit', 'hPa'),
  );
  $form['yc']['yr_verdata_precip_unit'] = array(
    '#type' => 'select',
    '#title' => t('Precipitation unit'),
    '#options' => drupal_map_assoc(array('mm', 'in')),
    '#default_value' => variable_get('yr_verdata_precip_unit', 'mm'),
  );
  $form['yc']['yr_verdata_windspeed_unit'] = array(
    '#type' => 'select',
    '#title' => t('Wind speed unit'),
    '#options' => array('m/s' => t('Meters per second'), 'knots' => t('Knots'), 'km/h' => t('Kilometers per hour'), 'mph' => t('Miles per hour')),
    '#default_value' => variable_get('yr_verdata_windspeed_unit', 'mps'),
  );

  $form['yd'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display options'),
    '#collapsible' => TRUE,
  );
  $locreg = t('Location, Region');
  $loccoun = t('Location, Country');
  $form['yd']['yr_verdata_name_display'] = array(
    '#type' => 'select',
    '#title' => t('Location name format'),
    '#options' => array(4 => t('Location'), 2 => $locreg, 1 => $loccoun),
    '#default_value' => variable_get('yr_verdata_name_display', 1),
    '#description' => t('How the location name should be output in page titles and listings. Note that if you set this to %locreg and the location name is the same as the region name, the output will use a fallback.', array('%locreg' => $locreg)),
  );
  $form['yd']['yr_verdata_name_fallback'] = array(
    '#type' => 'select',
    '#title' => t('Location name fallback'),
    '#options' => array(4 => t('Just the location name'), 1 => $loccoun),
    '#default_value' => variable_get('yr_verdata_name_fallback', 4),
    '#description' => t('How the location name fallback should work.'),
  );
  $form['yd']['yr_verdata_order'] = array(
    '#type' => 'select',
    '#title' => t('Sorting'),
    '#options' => array('name' => t('Name'), 'weight' => t('Weight')),
    '#default_value' => variable_get('yr_verdata_order', 'weight'),
    '#description' => t('How to sort locations in the block and overview page.'),
  );
  $form['yd']['yr_verdata_group'] = array(
    '#type' => 'select',
    '#title' => t('Grouping'),
    '#options' => array('off' => t('No grouping'), 'region' => t('Region'), 'country' => t('Country'), 'lang' => t('Language')),
    '#default_value' => variable_get('yr_verdata_group', 'off'),
    '#description' => t('Locations can be grouped according to region, country or the language the forecast is collected in.'),
  );
  $form['yd']['yr_verdata_npp'] = array(
    '#type' => 'textfield',
    '#size' => 3,
    '#title' => t('Paging'),
    '#default_value' => variable_get('yr_verdata_npp', 0),
    '#description' => t('You can use a pager on the overview page if you have a lot of locations. Set the number for how many locations to display per page. Enter "0" for no pager.'),
  );
  $form['yd']['yr_verdata_multiblocks'] = array(
    '#type' => 'radios',
    '#title' => t('Multiple blocks'),
    '#options' => array('on' => t('On'), 'off' => t('Off')),
    '#default_value' => variable_get('yr_verdata_multiblocks', 'off'),
    '#description' => t('Yr verdata provides one block, listing all locations. If you want to, it can additionally provide one block for each location. Note that this may look cluttered, so it can be a good idea to use page-specific settings for these blocks.'),
  );
  $form['yd']['yr_verdata_randomblock'] = array(
    '#type' => 'radios',
    '#title' => t('Random block'),
    '#options' => array('on' => t('On'), 'off' => t('Off')),
    '#default_value' => variable_get('yr_verdata_randomblock', 'off'),
    '#description' => t('Yr verdata provides one block, listing all locations. If you want to, it can additionally provide a block that shows the forecast for a random location. Note that this will make a database query on each page load for the random select. This is a small request, but with VERY high traffic, it could be a potential performance issue. The generated output will be cached for each location. All the other blocks are cached before the database is queried, so they are not affected by this.'),
  );

  $form['yt'] = array(
    '#type' => 'fieldset',
    '#title' => t('Theming options'),
    '#description' => t('A few options that can be used if you are making Yr weatherdata fit your theme. These values should only be altered if you know what you are doing and why you are doing them.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['yt']['yr_verdata_symbol_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Symbol image directory'),
    '#description' => t("The absolute path to the directory where you keep your symbol images (including trailing slash). Note that they should be named according to yr.no's scheme, which is partially documented at !symdoc. You can also study the xml files to figure it out. Note that the implementation in this module is actually a theme function, so you could alter that one too, to entirely fit your own needs through a theme hook.", array('!symdoc' => l('api.yr.no', 'http://api.yr.no/weatherapi/weathericon/1.0/documentation'))),
    '#default_value' => variable_get('yr_verdata_symbol_url', 'http://symbol.yr.no/grafikk/sym/b38/'),
  );
  $form['yt']['yr_verdata_wind_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Wind arrow image directory'),
    '#description' => t("The absolute path to the location where you keep or generate your wind arrow images (including trailing slash). Note that they should be named according to yr.no's scheme, which are auto-generated arrows based on speed and direction. This is not really documented, but you can check the source code in !module at around line 660 to see how I calculate it. Note that the implementation in this module is actually a theme function, so you could alter that one too, to entirely fit your own needs through a theme hook.", array('!module' => l('yr_verdata.module', 'http://drupalcode.org/viewvc/drupal/contributions/modules/yr_verdata/yr_verdata.module?view=markup&pathrev=DRUPAL-7--1'))),
    '#default_value' => variable_get('yr_verdata_wind_url', 'http://fil.nrk.no/yr/grafikk/vindpiler/32/'),
  );

  $form['yr_verdata_maxage'] = array(
    '#type' => 'select',
    '#title' => t('Forecast maxage'),
    '#options' => array(0 => t('Always update (development only!)'), 3600 => t('One hour'), 10800 => t('Three hours'), 21600 => t('Six hours (recommended)'), 43200 => t('12 hours'), 86800 => t('24 hours')),
    '#default_value' => variable_get('yr_verdata_maxage', 21600),
    '#description' => t('The longest time that will pass before the module attempts to update the locally stored forecast with a new one from yr.no. Note that yr.no does not update most locations more often than every 5-6 hours. Yr.no will block ip-addresses that request forecasts too often.'),
  );
  return system_settings_form($form);
}

/**
 * Submit handler for yr_verdata_settings().
 */
function yr_verdata_settings_submit($form, &$form_state) {
  // If the user hit the 'Reset to defaults button' we do that then return.
  if ($form_state['clicked_button']['#parents'][0] == 'reset') {
//    variable_set('yr_verdata_date_format', 'small');
    variable_set('yr_verdata_temp_unit', 'celsius');
    variable_set('yr_verdata_press_unit', 'hPa');
    variable_set('yr_verdata_precip_unit', 'mm');
    variable_set('yr_verdata_windspeed_unit', 'mps');
    variable_set('yr_verdata_name_display', 4);
    variable_set('yr_verdata_name_fallback', 4);
    variable_set('yr_verdata_maxage', 21600);
    variable_set('yr_verdata_order', 'weight');
    variable_set('yr_verdata_group', 'off');
    variable_set('yr_verdata_npp', 0);
    variable_set('yr_verdata_multiblocks', 'off');
    variable_set('yr_verdata_randomblock', 'off');
    variable_set('yr_verdata_symbol_url', 'http://symbol.yr.no/grafikk/sym/b38/');
    variable_set('yr_verdata_wind_url', 'http://fil.nrk.no/yr/grafikk/vindpiler/32/');
    drupal_set_message(t('The configuration options have been reset to their default values.'));
  }
  else {
    foreach ($form_state['values'] as $key => $value) {
      if (drupal_substr($key, 0, 10) == 'yr_verdata') variable_set($key, $value);
      // Remove any multiblocks, if that feature was disabled.
      if ($key == 'yr_verdata_multiblocks' && $value == 'off') {
        $result = db_query("SELECT * FROM {yr_verdata} ORDER BY name ASC");
        $records = $result->fetchAll();
        foreach ($records as $record) {
          $delta = 'yr_verdata_block_' . $record->yid;
          db_query("UPDATE {blocks} SET status = 0 WHERE module = 'yr_verdata' AND delta = '%s'", $delta);
        }
      }
      // Remove the randomblock, if that feature was disabled.
      if ($key == 'yr_verdata_randomblock' && $value == 'off') {
        db_query("UPDATE {blocks} SET status = 0 WHERE module = 'yr_verdata' AND delta = 'yr_verdata_randomblock'");
      }
    }
    drupal_set_message(t('Settings saved.'));
  }
  // And since we want changes to show up immediately, we clear the cache.
  cache_clear_all('yr_verdata', 'cache_page', TRUE);
}

/**
 * Function for adding locations to the database table.
 */
function yr_verdata_add_form() {
  $form['yvo'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add location by URL'),
  );
  $form['yvo']['url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#description' => t('The base URL to the forecast for this location. For example !example_url.', array('!example_url' => l(t('http://www.yr.no/sted/Norge/Vest-Agder/Kristiansand/Kristiansand/'), 'http://www.yr.no/sted/Norge/Vest-Agder/Kristiansand/Kristiansand/'))),
    '#size' => 60,
    '#required' => TRUE,
  );
  $form['yvo']['weight'] = array(
    '#type' => 'select',
    '#title' => t('Weight'),
    '#options' => drupal_map_assoc(array(1, 2, 3, 4, 5, 6, 7, 8, 9)),
    '#default_value' => 5,
    '#description' => t('Lower values will be displayed first in listings, tables and blocks. Note: This depends on the sorting settings in the !conf page.', array('!conf' => l(t('configuration'), 'admin/settings/yr_verdata'))),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add location'),
  );
  drupal_set_breadcrumb(array(l(t('Home'), '<front>'), l(t('Forecast'), 'forecast')));
  return $form;
}

/**
 * Validation handler for yr_verdata_add_form().
 */
function yr_verdata_add_form_validate($form, &$form_state) {
  // Verify that the url entered is actually for yr.no.
  $start = drupal_substr($form_state['values']['url'], 0, 17);
  if ($start !== 'http://www.yr.no/') {
    form_set_error('url', t('The url must be a valid yr.no address. Please include "www", because yr.no defaults to that convention.'));
  }
  // Check if the location already exists.
  $url = trim($form_state['values']['url']);
  // Make sure we are not using yr.no's cache, which sometimes adds numbers at the end of a url.
  $tilde = mb_strpos($url, '~');
  if ($tilde == TRUE) {
    $url = drupal_substr($url, 0, $tilde);
  }
  // Make sure we always have a trailing slash.
  if (drupal_substr($url, -1) != '/') {
    $url .= '/';
  }
  $result = db_query("SELECT yid FROM {yr_verdata} WHERE url = '%s'", $url);
  if (db_fetch_object($result)) {
    form_set_error('url', t('The location already exists in the database.'));
  }
}

/**
 * Submit handler for yr_verdata_add_form().
 */
function yr_verdata_add_form_submit($form, &$form_state) {
  $url = trim($form_state['values']['url']);
  // Make sure we are not using yr.no's cache, which sometimes adds numbers at the end of a url.
  $tilde = mb_strpos($url, '~');
  if ($tilde == TRUE) {
    $url = drupal_substr($url, 0, $tilde);
  }
  // Make sure we always have a trailing slash.
  if (drupal_substr($url, -1) != '/') {
    $url .= '/';
  }
  // Figure out what language this is.
  $components = explode('/', drupal_substr($url, 17, -1));
  switch ($components[0]) {
    case 'place' : // English
      $lang = 'en';
      break;
    case 'sted' : // Norwegian Bokmål
      $lang = 'nb';
      break;
    case 'stad' : // Norwegian Nynorsk
      $lang = 'nn';
      break;
    case 'paikka' : // Kvääni
      $lang = 'no-kv';
      break;
    case 'sadji' : // Sami
      $lang = 'smi';
      break;
  }
  $n = count($components) - 1;
  $file = md5($url) . '.xml';
  $name = str_replace('_', ' ', trim($components[$n])); // I think this is the only character we need to replace for pretty names.
  $region = str_replace('_', ' ', trim($components[2])); // I think this is the only character we need to replace for pretty names.
  $country = str_replace('_', ' ', trim($components[1])); // I think this is the only character we need to replace for pretty names.
  $query = "INSERT INTO {yr_verdata} (url, lang, file, weight, name, region, country) VALUES ('%s', '%s', '%s', %d, '%s', '%s', '%s')";
  if (db_query($query, $url, $lang, $file, $form_state['values']['weight'], $name, $region, $country)) {
    drupal_set_message(t('Location added.'));
    $id = db_last_insert_id('yr_verdata', 'yid');
    $location = new stdClass;
    $location->file = $file;
    $location->url = $url;
    $location->yid = $id;
    _yr_verdata_refresh_xml($location);
    // Flush the cache. We flush all of yr_verdata's cached stuff,
    // for simplicity. Maybe I'm just being lazy, but it's late...
    cache_clear_all('yr_verdata', 'cache_page', TRUE);
  }
  else {
    drupal_set_message(t('The location at @url could not be added to the database. If this problem persists, the administrator should be notified.', array('@url' => $url)));
  }
}

/**
 * Function for deleting locations from the database table.
 *
 * @param $yid
 * The unique id of the location.
 * @return
 * Returns a confirmation form for deleting the given location.
 */
function yr_verdata_delete_confirm($form, $yid) {
  $location = yr_verdata_load_location($yid, TRUE);
  if ($location['status'] == TRUE) {  
    $form = array();
    $form['yid'] = array(
      '#type' => 'hidden',
      '#value' => $yid,
    );
    $form['filename'] = array(
      '#type' => 'hidden',
      '#value' => $location['data']->filepath,
    );
    $question = t('Are you sure you want to remove the location %location, ID %yid from the database?', array('%location' => $location['data']->name, '%yid' => $location['data']->yid));
    $description = t('The location and all related data will be removed from your site. You can re-add it later at !add.', array('!add' => l('forecast/add', 'forecast/add')));
    $yes = t('Remove');
    return confirm_form($form, $question, 'forecast', $description, $yes);
  }
  else {
    $msg = t('No location found with the given ID.');
    drupal_set_message($msg, 'error');
    drupal_goto('forecast');
  }
}

/**
 * Submit handler for the delete location form.
 */
function yr_verdata_delete_confirm_submit($form, &$form_state) {
  // The user wanted this location gone. Delete it from the database.
  db_query("DELETE FROM {yr_verdata} WHERE yid = %d", $form_state['values']['yid']);
  // Clean out the stored xml file.
  file_delete($form_state['values']['filename']);
  // Flush the cache. We flush all of yr_verdata's cached stuff,
  // for simplicity. Maybe I'm just being lazy, but it's late...
  cache_clear_all('yr_verdata', 'cache_page', TRUE);
  // Redirect.
  drupal_set_message(t('The location was deleted.'));
  drupal_goto('forecast');
}








