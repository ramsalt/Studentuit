<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function views_gallery_user_default_permissions() {
  $permissions = array();

  // Exported permission: create gallery content
  $permissions['create gallery content'] = array(
    'name' => 'create gallery content',
    'roles' => array(),
  );

  // Exported permission: create gallery_image content
  $permissions['create gallery_image content'] = array(
    'name' => 'create gallery_image content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: delete any gallery content
  $permissions['delete any gallery content'] = array(
    'name' => 'delete any gallery content',
    'roles' => array(),
  );

  // Exported permission: delete any gallery_image content
  $permissions['delete any gallery_image content'] = array(
    'name' => 'delete any gallery_image content',
    'roles' => array(),
  );

  // Exported permission: delete own gallery content
  $permissions['delete own gallery content'] = array(
    'name' => 'delete own gallery content',
    'roles' => array(),
  );

  // Exported permission: delete own gallery_image content
  $permissions['delete own gallery_image content'] = array(
    'name' => 'delete own gallery_image content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit any gallery content
  $permissions['edit any gallery content'] = array(
    'name' => 'edit any gallery content',
    'roles' => array(),
  );

  // Exported permission: edit any gallery_image content
  $permissions['edit any gallery_image content'] = array(
    'name' => 'edit any gallery_image content',
    'roles' => array(),
  );

  // Exported permission: edit own gallery content
  $permissions['edit own gallery content'] = array(
    'name' => 'edit own gallery content',
    'roles' => array(),
  );

  // Exported permission: edit own gallery_image content
  $permissions['edit own gallery_image content'] = array(
    'name' => 'edit own gallery_image content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache reg
  $permissions['view imagecache reg'] = array(
    'name' => 'view imagecache reg',
    'roles' => array(
      '0' => 'anonymous user',
    ),
  );

  // Exported permission: view imagecache short
  $permissions['view imagecache short'] = array(
    'name' => 'view imagecache short',
    'roles' => array(
      '0' => 'anonymous user',
    ),
  );

  // Exported permission: view imagecache thumb
  $permissions['view imagecache thumb'] = array(
    'name' => 'view imagecache thumb',
    'roles' => array(
      '0' => 'anonymous user',
    ),
  );

  // Exported permission: view imagecache tiny
  $permissions['view imagecache tiny'] = array(
    'name' => 'view imagecache tiny',
    'roles' => array(
      '0' => 'anonymous user',
    ),
  );

  return $permissions;
}
