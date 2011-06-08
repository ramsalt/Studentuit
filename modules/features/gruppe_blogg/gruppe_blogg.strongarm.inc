<?php

/**
 * Implementation of hook_strongarm().
 */
function gruppe_blogg_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_bloggpost';
  $strongarm->value = 0;

  $export['comment_anonymous_bloggpost'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_bloggpost';
  $strongarm->value = '2';

  $export['comment_bloggpost'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_bloggpost';
  $strongarm->value = '3';

  $export['comment_controls_bloggpost'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_bloggpost';
  $strongarm->value = '4';

  $export['comment_default_mode_bloggpost'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_bloggpost';
  $strongarm->value = '1';

  $export['comment_default_order_bloggpost'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_bloggpost';
  $strongarm->value = '50';

  $export['comment_default_per_page_bloggpost'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_bloggpost';
  $strongarm->value = '0';

  $export['comment_form_location_bloggpost'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_bloggpost';
  $strongarm->value = '1';

  $export['comment_preview_bloggpost'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_bloggpost';
  $strongarm->value = '1';

  $export['comment_subject_field_bloggpost'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_bloggpost';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );

  $export['node_options_bloggpost'] = $strongarm;
  return $export;
}
