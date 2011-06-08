<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function gruppe_kalender_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'gruppe_kalender';
  $context->description = 'kalender til grupper';
  $context->tag = 'gruppe';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'hendelse' => 'hendelse',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
    'views' => array(
      'values' => array(
        'Kalender' => 'Kalender',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-Kalender-block_1' => array(
          'module' => 'views',
          'delta' => 'Kalender-block_1',
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
    'menu' => 'kalender',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('gruppe');
  t('kalender til grupper');

  $export['gruppe_kalender'] = $context;
  return $export;
}
