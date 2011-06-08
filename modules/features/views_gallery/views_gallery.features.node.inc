<?php
// $Id: views_gallery.features.node.inc,v 1.2 2010/06/05 13:56:24 karens Exp $

/**
 * Helper to implementation of hook_node_info().
 */
function _views_gallery_node_info() {
  $items = array(
    'gallery' => array(
      'name' => t('Gallery'),
      'module' => 'features',
      'description' => t('A gallery for a collection of photos.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Description'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'gallery_image' => array(
      'name' => t('Image'),
      'module' => 'features',
      'description' => t('An individual gallery photograph.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Description'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
