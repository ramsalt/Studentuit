<?php
/**
 * @file Admin pages for ScribdField.
 */

/**
 * Configure ScribdField integration with Scribd.com.
 */
function scribdfield_admin_settings_form(&$form_state) {
  $form = array();

  $form['scribd_api_key'] = array(
    '#default_value' => variable_get('scribd_api_key', NULL),
    '#title'         => t('Scribd API key'),
    '#required'      => TRUE,
    '#type'          => 'textfield',
  );

  $form['scribdfield_security'] = array(
    '#collapsible'   => TRUE,
    '#title'         => t('Settings for encrypted PDFs on Scribd'),
    '#type'          => 'fieldset',
  );

  $form['scribdfield_security']['scribd_api_secret'] = array(
    '#default_value' => variable_get('scribd_api_secret', NULL),
    '#description'   => t('Required for using secure files or disabling printing.'),
    '#title'         => t('API secret'),
    '#type'          => 'textfield',
  );

  $form['scribdfield_security']['scribd_secure_files'] = array(
    '#default_value' => variable_get('scribd_secure_files', NULL),
    '#title'         => t('Use secure, non-downloadable, Scribd files.'),
    '#type'          => 'checkbox',
  );

  $form['scribdfield_security']['scribd_disable_print'] = array(
    '#default_value' => variable_get('scribd_disable_print', NULL),
    '#title'         => t('Disable printing for Scribd files, requires secure files and API key.'),
    '#type'          => 'checkbox',
  );

  $form['api'] = array(
    '#title'        => t('API settings'),
    '#type'         => 'fieldset',
  );

  $form['api']['scribdfield_request_framework'] = array(
    '#type'         => 'select',
    '#title'        => t('Request framework'),
    '#description'  => t('Select the prefered request framework to use for making requests.'),
    '#options'      => array(
      SCRIBDFIELD_PLATFORM_EITHER => t('Either'),
      SCRIBDFIELD_PLATFORM_CURL => t('Curl'),
      SCRIBDFIELD_PLATFORM_FOPEN => t('Fopen'),
    ),
    '#default_value' => variable_get('scribdfield_request_framework', SCRIBDFIELD_PLATFORM_EITHER),
  );

  $form['api']['scribdfield_log_requests'] = array(
    '#type'          => 'select',
    '#title'         => t('Logging'),
    '#description'   => t('Select logging status for requests.'),
    '#options'       => array(
      1 => t('On'),
      0 => t('Off'),
    ),
    '#default_value' => variable_get('scribdfield_log_requests', 0),
  );

  return system_settings_form($form);
}

/**
 * Validation for admin settings form.
 */
function scribdfield_admin_settings_form_validate($form, &$form_state) {
  $secret = trim($form_state['values']['scribd_api_secret']);

  if (empty($secret) && ($form_state['values']['scribd_secure_files'] || $form_state['values']['scribd_secure_files'])) {
    form_set_error('scribdfield_security][scribd_api_secret', t('For secure files or disabled printing to work, you must set the API secret.'));
  }
}

