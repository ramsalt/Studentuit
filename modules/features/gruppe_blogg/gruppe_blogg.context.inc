<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function gruppe_blogg_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'gruppe_blogg';
  $context->description = 'Bloggverktøyet i en gruppe';
  $context->tag = 'gruppe';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'bloggpost' => 'bloggpost',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
    'views' => array(
      'values' => array(
        'blogg' => 'blogg',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'comment-0' => array(
          'module' => 'comment',
          'delta' => 0,
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
    'menu' => 'blogg',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Bloggverktøyet i en gruppe');
  t('gruppe');

  $export['gruppe_blogg'] = $context;
  return $export;
}
