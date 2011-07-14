<?php
// $Id: og_access_roles.views.inc,v 1.1 2009/12/31 01:00:20 marcp Exp $
/**
 * @file
 * Provide views data and handlers for og_access_roles.module
 */

/**
 * Implementation of hook_views_handlers().
 */
function og_access_roles_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'og_access_roles') . '/includes/views/handlers',
    ),
    'handlers' => array(
      'og_access_roles_handler_field_rid' => array(
        'parent' => 'views_handler_field_prerender_list',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_data().
 */
function og_access_roles_views_data() {
  // Basic table information.
  $data['og_access_roles']['table']['group']  = t('Organic groups');

  // Join to 'node' as a base table.
  $data['og_access_roles']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'role' => array(
      'left_table' => 'role',
      'left_field' => 'rid',
      'field' => 'rid',
    ),
  );

  // ----------------------------------------------------------------
  // Fields

  // Roles that have access to a node via og_access_roles
  $data['og_access_roles']['rid'] = array(
    'title' => t('Roles with access'),
    'help' => t('Roles that have access to a node via og_access_roles.'),
    'field' => array(
      'handler' => 'og_access_roles_handler_field_rid',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_user_roles',
      'numeric' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_users_roles_rid',
      'name table' => 'role',
      'name field' => 'name',
      'empty field name' => t('No role'),
      'numeric' => TRUE,
    ),
  );

  return $data;
}
