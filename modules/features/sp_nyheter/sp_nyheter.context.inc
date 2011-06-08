<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function sp_nyheter_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'site_nyheter';
  $context->description = '';
  $context->tag = 'site';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'sp_nyheter' => 'sp_nyheter',
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
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('site');

  $export['site_nyheter'] = $context;
  return $export;
}
