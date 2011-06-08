<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function sp_dokumenter_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function sp_dokumenter_node_info() {
  $items = array(
    'dokument' => array(
      'name' => t('Dokument'),
      'module' => 'features',
      'description' => t('Brukes for å laste opp dokumenter: innkallinger, referater, reglement. '),
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
function sp_dokumenter_views_api() {
  return array(
    'api' => '2',
  );
}
