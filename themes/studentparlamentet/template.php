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
  $space = spaces_get_space();
  
  if ( $space ) {
    if( $space->type == 'og' ) {
      // If we are in OG use template for page customized for OG
      $vars['template_files'] = array('og-page');
      
      // Get 
      $sql = 'SELECT uid
              FROM {og_uid}
              WHERE is_admin = 1 AND nid = %d AND uid = %d';
      
      $result = db_result(db_query($sql, $space->id, $user->uid));
      
      // Result is true if current user is admin for this group, superadmin or administrator
      if ($result || $user->uid == 1 || array_key_exists(6, $user->roles) ) { 
        
        // $vars['space_settings'] kan fjernes etter oppgradering
        // se litt mer på styles her
        $vars['space_settings'] = '<ul class="links admin-links"><li class="space-settings first">' . l("Administrer", "node/" . $space->id . "/edit") . '</li></ul>';
        $space_settings_links[] = l("Edit group", "node/" . $space->id . "/edit");
        $space_settings_links[] = l("Group features", "node/" . $space->id . "/features");
        $space_settings_links[] = l("Members", $space->group->purl . "/og/users/" . $space->id);
        $space_settings_links[] = l("Add members", $space->group->purl . "/og/users/" . $space->id . "/add_user");
        $space_settings_links[] = '<a href="' . base_path() . 'grupper">' . t('Show all groups') . '</a>'; //l("Show all groups", "/" . base_path() . "grupper");
        drupal_add_js(drupal_get_path('theme','studentparlamentet'.'includes/banner_menu.js'));
      }
    }
    
    foreach($space_settings_links as $link) {
      $_links .= '<li>' . $link . '</li>';
    }
    
    if( $_links ) {
      $_links = '<ul>' . $_links . '</ul>';
    }
    else {
      $_links = FALSE;
    }
    
    
    $vars['space_settings_flyout'] = $_links;
  }
/*
  if($user && $user->uid > 0) {
    $userlinks = array();
    
    $userlinks['username'] = array(
      'title' => t('Welcome,') . ' ' . $user->name,
      'href' => 'user/' . $user->uid,
    );
    
    $userlinks['usermessages'] = array(
      'title' => '(12)',
      'href' => 'user/messages',
      'attributes' => array(
        'class' => 'messages',
      ),
    );
    
    $userlinks['userlogout'] = array(
      'title' => t('Logout'),
      'href' => 'logout',
    );
    
    
    $vars['usermenu'] = theme('links', $userlinks);
  }
  else {
    
    $userlinks['loginmessage'] = array(
      'title' => 'Du er ikke logget inn',
    );
    
    $userlinks['userlogin'] = array(
      'title' => 'Logg inn',
      'href' => 'user/login',
    );
    
    $userlinks['userregister'] = array(
      'title' => 'Registrer konto',
      'href' => 'user/register',
    );
    
    $vars['usermenu'] = theme('links', $userlinks);
  }
  */ 

  // Get reference to current space
  $space = spaces_get_space();  
  // If we are in space, prepare and send space related variables to template
  if ($space) { 
    $vars['spacetype'] = $space->type;
    $vars['spacetitle'] = l($space->group->title, '<front>');
  }
  
  
  
  /**
   * I følgende situasjoner, legg til "Opprett ny <content type>" hvis bruker er
   * på en node eller utlisting av en feature ala. blogg, kalender etc.
   */
  
  /*
  $urls = array(
    'blogg' => 'blog',
    'kalender' =>  'activity',
    'nyheter' => 'news',
  ); 
  
  $arg = arg();
  
  
  if (count($arg) == 1 && array_key_exists($arg[0], $urls)) {
    $_node_type = $urls[$arg[0]];
  }
  
  
  if( count($arg) >= 2 && $arg[0] == 'node' && (int)$arg[1] ) {
    $_node = node_load($arg[1]);
    $_node_type = $_node->type;    
  }
  
  if ($_node_type) {
    
    $types_names = node_get_types('names');
    $excluded_content_types = array('minisite', 'newsold', 'page', 'profile');
    
    if (node_access('create', $_node->type) || !in_array($_node->type, $excluded_content_types)) {
      $block = new stdclass;
      $block->delta = 'content-creation-link';
      $block->module = 'template-preprocess-page';
      $block->content = l('Opprett ny ' . strtolower($types_names[$_node_type]), 'node/add/' . $_node_type) . '</div>';
      
      $vars['right'] = theme('block', $block) . $vars['right'];
    }
  }
  */ 
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
  // Process images array into an array of filepaths & add processed
  // version to page template.

  /*
  foreach ($image as $name => $fid) {
    $file = db_fetch_object(db_query('SELECT * FROM {files} f WHERE f.fid = %d', $fid));
    if ($file && $file->filepath && file_exists($file->filepath)) {
      $image[$name] = $file->filepath;
      $vars[$name] = theme('designkit_image', $name, $file->filepath);
    }
    else {
      unset($image[$name]);
    }
  }
  */ 
  // Generate CSS styles.
  /*
  if ($image || array_filter($color, 'designkit_valid_color')) {
    // Add in designkit styles.
    $vars['body_classes'] .= " designkit";
    // Add styles.
    $styles = theme('designkit', $color, $image);
    // Provide in separate variable for themes that reset or blow away styles.
    $vars['styles'] .= $styles;
    $vars['designkit'] = $styles;
  }
  */ 
}

?>
