<?php

/**
 * Implementation of hook_strongarm().
 */
function views_gallery_og_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_gallery';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_gallery'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_gallery_image';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_gallery_image'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_max_groups_gallery';
  $strongarm->value = '';

  $export['og_max_groups_gallery'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_max_groups_gallery_image';
  $strongarm->value = '';

  $export['og_max_groups_gallery_image'] = $strongarm;
  return $export;
}
