<?php 

function parlamentet_preprocess_page(&$vars, $hook) {
  // Get reference to current space
  $space = spaces_get_space();

  // If we are in space, prepare and send space related variables to template
  if ($space) { 
    $vars['spacetype'] = $space->type;
    $vars['spacetitle'] = l($space->group->title, '<front>');
  }
}
