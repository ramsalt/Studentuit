<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function sp_dokumenter_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'site_dokumenter';
  $context->description = 'Dokumentarkiv';
  $context->tag = 'site';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'dokumenter' => 'dokumenter',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'system-0' => array(
          'module' => 'system',
          'delta' => 0,
          'region' => 'bottom_grid_1',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Dokumentarkiv');
  t('site');

  $export['site_dokumenter'] = $context;
  return $export;
}
