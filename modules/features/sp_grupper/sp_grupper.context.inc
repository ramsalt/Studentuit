<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function sp_grupper_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'site_gruppeoversikt';
  $context->description = 'Oversikt over grupper ';
  $context->tag = 'site';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'gruppeoversikt' => 'gruppeoversikt',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'og-3' => array(
          'module' => 'og',
          'delta' => 3,
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Oversikt over grupper ');
  t('site');

  $export['site_gruppeoversikt'] = $context;
  return $export;
}
