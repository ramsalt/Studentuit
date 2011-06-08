<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function sp_forside_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'site_frontpage';
  $context->description = 'Forside til studentparlamentet';
  $context->tag = 'site';
  $context->conditions = array(
    'menu' => array(
      'values' => array(
        'hjem' => 'hjem',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-site_featured-block_1' => array(
          'module' => 'views',
          'delta' => 'site_featured-block_1',
          'region' => 'content_top',
          'weight' => 0,
        ),
        'views-site_kalender-block_1' => array(
          'module' => 'views',
          'delta' => 'site_kalender-block_1',
          'region' => 'content_bottom',
          'weight' => 0,
        ),
        'views-grupper-block_1' => array(
          'module' => 'views',
          'delta' => 'grupper-block_1',
          'region' => 'right',
          'weight' => 0,
        ),
        'views-site_blogg-block_1' => array(
          'module' => 'views',
          'delta' => 'site_blogg-block_1',
          'region' => 'right',
          'weight' => 1,
        ),
        'yr_verdata-3' => array(
          'module' => 'yr_verdata',
          'delta' => '3',
          'region' => 'right',
          'weight' => 2,
        ),
        'views-Kalender-block_1' => array(
          'module' => 'views',
          'delta' => 'Kalender-block_1',
          'region' => 'right',
          'weight' => 3,
        ),
        'block-1' => array(
          'module' => 'block',
          'delta' => '1',
          'region' => 'right',
          'weight' => 4,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Forside til studentparlamentet');
  t('site');

  $export['site_frontpage'] = $context;
  return $export;
}
