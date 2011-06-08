<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function gruppe_forside_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'gruppe_forside';
  $context->description = 'Forsiden til en gruppe';
  $context->tag = 'gruppe';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'hei' => 'hei',
        'hei/' => 'hei/',
        'hei/*' => 'hei/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'gruppe_forside-0' => array(
          'module' => 'gruppe_forside',
          'delta' => 0,
          'region' => 'content_bottom',
          'weight' => 0,
        ),
        'views-Kalender-block_1' => array(
          'module' => 'views',
          'delta' => 'Kalender-block_1',
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
    'menu' => 'hei',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Forsiden til en gruppe');
  t('gruppe');

  $export['gruppe_forside'] = $context;
  return $export;
}
