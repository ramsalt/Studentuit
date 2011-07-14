<?php
// $Id: og_access_roles_handler_field_rid.inc,v 1.1 2009/12/31 01:00:20 marcp Exp $
/**
 * @file
 * Field handler to provide a list of the roles that have access
 * to nodes via og_access_roles.
 */

/**
 * Field handler to provide a list of the roles that have access
 * to nodes.
 */
class og_access_roles_handler_field_rid extends views_handler_field_prerender_list {
  function construct() {
    parent::construct();
    $this->additional_fields['nid'] = array('table' => 'node', 'field' => 'nid');
  }

  function query() {
    $this->add_additional_fields();
    $this->field_alias = $this->aliases['nid'];
  }

  function pre_render($values) {
    $this->items = array();

    foreach ($values as $result) {
      if (!empty($result->{$this->aliases['nid']})) {
        $nids[] = $result->{$this->aliases['nid']};
      }
    }

    if ($nids) {
      $result = db_query("SELECT o.nid, o.rid, r.name FROM {role} r INNER JOIN {og_access_roles} o ON o.rid = r.rid WHERE o.nid IN (" . implode(', ', $nids) . ") ORDER BY r.name");
      while ($role = db_fetch_object($result)) {
        $this->items[$role->nid][$role->rid]['role'] = check_plain($role->name);
        $this->items[$role->nid][$role->rid]['rid'] = $role->rid;
      }
    }
  }

  function render_item($count, $item) {
    return $item['role'];
  }

  function document_self_tokens(&$tokens) {
    $tokens['[' . $this->options['id'] . '-role' . ']'] = t('The name of the role.');
    $tokens['[' . $this->options['id'] . '-rid' . ']'] = t('The role ID of the role.');
  }

  function add_self_tokens(&$tokens, $item) {
    $tokens['[' . $this->options['id'] . '-role' . ']'] = $item['role'];
    $tokens['[' . $this->options['id'] . '-rid' . ']'] = $item['rid'];
  }
}
