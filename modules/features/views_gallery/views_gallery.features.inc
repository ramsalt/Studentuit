<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function views_gallery_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function views_gallery_imagecache_default_presets() {
  $items = array(
    'reg' => array(
      'presetname' => 'reg',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_deprecated_scale',
          'data' => array(
            'fit' => 'inside',
            'width' => '500',
            'height' => '1000',
          ),
        ),
      ),
    ),
    'short' => array(
      'presetname' => 'short',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_deprecated_scale',
          'data' => array(
            'fit' => 'outside',
            'width' => '150',
            'height' => '150',
          ),
        ),
        '1' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_crop',
          'data' => array(
            'width' => '150',
            'height' => '75',
            'xoffset' => 'center',
            'yoffset' => 'center',
          ),
        ),
      ),
    ),
    'thumb' => array(
      'presetname' => 'thumb',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_deprecated_scale',
          'data' => array(
            'fit' => 'outside',
            'width' => '200',
            'height' => '150',
          ),
        ),
        '1' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_crop',
          'data' => array(
            'width' => '200',
            'height' => '150',
            'xoffset' => 'center',
            'yoffset' => 'center',
          ),
        ),
      ),
    ),
    'tiny' => array(
      'presetname' => 'tiny',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '60',
            'height' => '60',
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function views_gallery_node_info() {
  $items = array(
    'gallery' => array(
      'name' => t('Galleri'),
      'module' => 'features',
      'description' => t('A gallery for a collection of photos.'),
      'has_title' => '1',
      'title_label' => t('Tittel'),
      'has_body' => '1',
      'body_label' => t('Beskrivelse'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'gallery_image' => array(
      'name' => t('Bilde'),
      'module' => 'features',
      'description' => t('An individual gallery photograph.'),
      'has_title' => '1',
      'title_label' => t('Tittel'),
      'has_body' => '1',
      'body_label' => t('Beskrivelse'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function views_gallery_views_api() {
  return array(
    'api' => '2',
  );
}
