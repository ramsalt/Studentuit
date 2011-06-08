<?php
// $Id: views_gallery.defaults.inc,v 1.2 2010/06/05 13:56:24 karens Exp $

/**
 * Helper to implementation of hook_content_default_fields().
 */
function _views_gallery_content_default_fields() {
  $fields = array();

  // Exported field: field_gallery
  $fields[] = array(
    'field_name' => 'field_gallery',
    'type_name' => 'gallery_image',
    'display_settings' => array(
      'weight' => '-2',
      'parent' => '',
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'inline',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '1',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'gallery' => 'gallery',
      'group' => 0,
      'gallery_image' => 0,
      'image' => 0,
      'page' => 0,
      'story' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'node_link' => array(
        'teaser' => 0,
        'full' => 1,
        'title' => 'Add photo',
        'hover_title' => 'Add a new photo to this gallery',
        'destination' => 'node',
      ),
      'fallback' => 'select',
      'edit_fallback' => 1,
      'label' => 'Gallery',
      'weight' => '-7',
      'description' => '',
      'type' => 'nodereference_url',
      'module' => 'nodereference_url',
    ),
  );

  // Exported field: field_gallery_image
  $fields[] = array(
    'field_name' => 'field_gallery_image',
    'type_name' => 'gallery_image',
    'display_settings' => array(
      'weight' => '-3',
      'parent' => '',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'thumb_linked',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'reg_linked',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'reg_linked',
      ),
      '2' => array(
        'format' => 'reg_linked',
      ),
      '3' => array(
        'format' => 'reg_linked',
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '1',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'jpg jpeg png gif',
      'file_path' => 'photos',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '2M',
      'max_filesize_per_node' => '',
      'max_resolution' => '640x400',
      'min_resolution' => 0,
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'label' => 'Image',
      'weight' => '-8',
      'description' => '',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Translatables
  array(
    t('Gallery'),
    t('Image'),
  );

  return $fields;
}

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _views_gallery_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Helper to implementation of hook_imagecache_default_presets().
 */
function _views_gallery_imagecache_default_presets() {
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
 * Helper to implementation of hook_user_default_permissions().
 */
function _views_gallery_user_default_permissions() {
  $permissions = array();

  // Exported permission: create gallery content
  $permissions[] = array(
    'name' => 'create gallery content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: create gallery_image content
  $permissions[] = array(
    'name' => 'create gallery_image content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: delete any gallery content
  $permissions[] = array(
    'name' => 'delete any gallery content',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: delete any gallery_image content
  $permissions[] = array(
    'name' => 'delete any gallery_image content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: delete own gallery content
  $permissions[] = array(
    'name' => 'delete own gallery content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: delete own gallery_image content
  $permissions[] = array(
    'name' => 'delete own gallery_image content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: edit any gallery content
  $permissions[] = array(
    'name' => 'edit any gallery content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: edit any gallery_image content
  $permissions[] = array(
    'name' => 'edit any gallery_image content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: edit own gallery content
  $permissions[] = array(
    'name' => 'edit own gallery content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: edit own gallery_image content
  $permissions[] = array(
    'name' => 'edit own gallery_image content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: view imagecache reg
  $permissions[] = array(
    'name' => 'view imagecache reg',
    'roles' => array(
      '0' => 'anonymous user',
    ),
  );

  // Exported permission: view imagecache short
  $permissions[] = array(
    'name' => 'view imagecache short',
    'roles' => array(
      '0' => 'anonymous user',
    ),
  );

  // Exported permission: view imagecache thumb
  $permissions[] = array(
    'name' => 'view imagecache thumb',
    'roles' => array(
      '0' => 'anonymous user',
    ),
  );

  // Exported permission: view imagecache tiny
  $permissions[] = array(
    'name' => 'view imagecache tiny',
    'roles' => array(
      '0' => 'anonymous user',
    ),
  );

  return $permissions;
}

/**
 * Helper to implementation of hook_strongarm().
 */
function _views_gallery_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_gallery';
  $strongarm->value = '0';

  $export['comment_gallery'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_gallery_image';
  $strongarm->value = array(
    'title' => '-9',
    'body_field' => '-6',
    'revision_information' => '-5',
    'comment_settings' => '-4',
    'menu' => '-10',
  );

  $export['content_extra_weights_gallery_image'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_gallery';
  $strongarm->value = array(
    '0' => 'status',
  );

  $export['node_options_gallery'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_gallery_image';
  $strongarm->value = array(
    '0' => 'status',
  );

  $export['node_options_gallery_image'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'views_gallery_gallery_type';
  $strongarm->value = 'gallery';

  $export['views_gallery_gallery_type'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'views_gallery_image_type';
  $strongarm->value = 'gallery_image';

  $export['views_gallery_image_type'] = $strongarm;

  return $export;
}
