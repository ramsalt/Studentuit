<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function gruppe_undersider_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function gruppe_undersider_node_info() {
  $items = array(
    'underside' => array(
      'name' => t('Underside'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Tittel'),
      'has_body' => '1',
      'body_label' => t('Brødtekst'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function gruppe_undersider_views_api() {
  return array(
    'api' => '2',
  );
}
