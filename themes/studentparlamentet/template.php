<?php


function studentparlamentet_preprocess_node(&$vars) {
  // lager tre datovariabler så man kan lage kalender-styling
  $node = $vars['node'];
  $vars['dato_dag'] = format_date($node->created, 'custom', 'j');
  $vars['dato_mnd'] = format_date($node->created, 'custom', 'M');
  $vars['dato_aar'] = format_date($node->created, 'custom', 'Y');
}

function studentparlamentet_preprocess_page(&$vars, $hook) {
  // Currently logged in user 
  global $user;
if(arg(0)=='user'){
	$vars['title'] = t('Login');  
}
  //if(function_exists('spaces_get_space')){
    $space = spaces_get_space();
  
  if ( $space ) {
    // If we are in space, prepare and send space related variables to template
    $vars['spacetype'] = $space->type;
    $vars['spacetitle'] = l($space->group->title, '<front>');
    
  }
  $banner=_make_banner_links($space);
  if($banner){
    $vars['space_settings_flyout'] = $banner;
  }

  // For easy printing of variables.
  $vars['logo_img']         = $vars['logo'] ? theme('image', substr($vars['logo'], strlen(base_path())), t('Home'), t('Home')) : '';
  $vars['linked_logo_img']  = $vars['logo_img'] ? l($vars['logo_img'], '<front>', array('rel' => 'home', 'title' => t('Home'), 'html' => TRUE)) : '';
  //$vars['linked_site_name'] = $vars['site_name'] ? l($vars['site_name'], '<front>', array('rel' => 'home', 'title' => t('Home'))) : '';
  $vars['main_menu_links']      = theme('links', $vars['primary_links'], array('class' => 'links main-menu'));
  $vars['secondary_menu_links'] = theme('links', $vars['secondary_links'], array('class' => 'links secondary-menu'));

  // Make sure framework styles are placed above all others.
  #$vars['css_alt'] = zen_ninesixty_css_reorder($vars['css']);
  #$vars['styles'] = drupal_get_css($vars['css_alt']);
  
  // This line of code was borrowed from conditional_style module (http://drupal.org/project/conditional_styles)
  $vars['styles'] .= $vars['conditional_styles'] = variable_get('conditional_styles_' . $GLOBALS['theme'], '');

  // Classes for body element. Allows advanced theming based on context
  // (home page, node of certain type, etc.)
  $classes = split(' ', $vars['body_classes']);
 

  $vars['body_classes_array'] = $classes;
  $vars['body_classes'] = implode(' ', $classes); // Concatenate with spaces.

  // vjo: får designkit til å virke i zen_ninesixty: http://drupal.org/node/814548#comment-3174320
  // note: hele designkit_preprocess_page fra designkit.module er kopiert inn for å få dette til å 
  // funke, men noe trengs kanskje ikke.. (?)

  /*
  $info = designkit_get_info();
  $color = !empty($info['designkit']['color']) ? variable_get('designkit_color', array()) : array();
  $image = !empty($info['designkit']['image']) ? variable_get('designkit_image', array()) : array();
  */ 
  
  // Clear out stale values for image keys. This prevents themes from
  // getting unexpected values if no images have been set.
  if (!empty($info['designkit']['image'])) {
    foreach (array_keys($info['designkit']['image']) as $name) {
      if (isset($vars[$name])) {
        unset($vars[$name]);
      }
    }
  }

}
function _make_banner_links($space = NULL){
  global $user;
  if ($user->uid == 1 || array_key_exists(4, $user->roles) || array_key_exists(3, $user->roles) ) {
    $space_settings_links[] = l(t('Add group'), 'node/add/gruppe');
    $space_settings_links[] = l(t('Users'), 'brukere');
  }
    if( $space->type == 'og' ) {
      // If we are in OG use template for page customized for OG
      $vars['template_files'] = array('og-page');
      
      // Get 
      $sql = 'SELECT uid
              FROM {og_uid}
              WHERE is_admin = 1 AND nid = %d AND uid = %d';
      
      $result = db_result(db_query($sql, $space->id, $user->uid));
      
      // Result is true if current user is admin for this group, superadmin or administrator
      if ($result || $user->uid == 1 || array_key_exists(4, $user->roles) || array_key_exists(3, $user->roles) ) { 
        
        // $vars['space_settings'] kan fjernes etter oppgradering
        // se litt mer på styles her
        $vars['space_settings'] = '<ul class="links admin-links"><li class="space-settings first">' . l(t("Administrer"), "node/" . $space->id . "/edit") . '</li></ul>';
        $space_settings_links[] = l(t("Edit group"), "node/" . $space->id . "/edit");
        $space_settings_links[] = l(t("Group features"), "node/" . $space->id . "/features");
        $space_settings_links[] = l(t("Members"), $space->group->purl . "/og/users/" . $space->id);
        $space_settings_links[] = l(t("Add members"), $space->group->purl . "/og/users/" . $space->id . "/add_user");
        $space_settings_links[] = '<a href="' . base_path() . 'grupper">' . t('Show all groups') . '</a>'; //l("Show all groups", "/" . base_path() . "grupper");
        $space_settings_links[] = l(t("All groups"), "user/".$user->uid."/edit/groups");
    
        
      }
    }

    foreach($space_settings_links as $link) {
      $_links .= '<li>' . $link . '</li>';
    }
    
    if( $_links ) {
      $_links = '<ul>' . $_links . '</ul>';
      drupal_add_js(drupal_get_path('theme','studentparlamentet').'/javascript/banner_menu.js');
    }
    else {
      $_links = FALSE;
    }
    
    
    return $_links;
}
?>
