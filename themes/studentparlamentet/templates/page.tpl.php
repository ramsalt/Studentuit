<?php
// $Id: page.tpl.php,v 1.11.2.2 2010/08/06 11:13:42 goba Exp $

/**
 * @file
 * Displays a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $css: An array of CSS files for the current page.
 * - $directory: The directory the theme is located in, e.g. themes/garland or
 *   themes/garland/minelli.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Page metadata:
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or
 *   'rtl'.
 * - $head_title: A modified version of the page title, for use in the TITLE
 *   element.
 * - $head: Markup for the HEAD element (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $body_classes: A set of CSS classes for the BODY tag. This contains flags
 *   indicating the current layout (multiple columns, single column), the
 *   current path, whether the user is logged in, and so on.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled in
 *   theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 * - $mission: The text of the site mission, empty when display has been
 *   disabled in theme settings.
 *
 * Navigation:
 * - $search_box: HTML to display the search box, empty if search has been
 *   disabled.
 * - $primary_links (array): An array containing primary navigation links for
 *   the site, if they have been configured.
 * - $secondary_links (array): An array containing secondary navigation links
 *   for the site, if they have been configured.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $left: The HTML for the left sidebar.
 * - $breadcrumb: The breadcrumb trail for the current page.
 * - $title: The page title, for use in the actual HTML content.
 * - $help: Dynamic help text, mostly for admin pages.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs: Tabs linking to any sub-pages beneath the current page (e.g., the
 *   view and edit tabs when displaying a node).
 * - $content: The main content of the current Drupal page.
 * - $right: The HTML for the right sidebar.
 * - $node: The node object, if there is an automatically-loaded node associated
 *   with the page, and the node ID is the second argument in the page's path
 *   (e.g. node/12345 and node/12345/revisions, but not comment/reply/12345).
 *
 * Footer/closing data:
 * - $feed_icons: A string of all feed icons for the current page.
 * - $footer_message: The footer message as defined in the admin settings.
 * - $footer : The footer region.
 * - $closure: Final closing markup from any modules that have altered the page.
 *   This variable should always be output last, after all other dynamic
 *   content.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>" xmlns:fb="http://www.facebook.com/2008/fbml">
<head>
<?php print $head ?>
<?php print $styles ?>
<?php print $scripts ?>
<title><?php print $head_title ?></title>


</head>

<body <?php // print drupal_attributes($attr); ?>>

<!-- start page wrap -->
<div class="page-wrap"><div class="page-wrap-content">
  
  <div id="sitebar">
    <div class="container_12 -clear-block">
      <div class="grid_12">
        <div class="sitebar-content">
          <div class="sitelinks">
            <div class="sitename">
              <a href="<?php print $base_path;?>">
              <img src="<?php print $directory;?>/images/home-icon.png"> 
              <p><?php print $site_name; ?></p>
              </a>
            </div>
              <div class="global-links">

                <?php // fjerner denne enn så lenge...
                //print theme('links', $secondary_links); ?>          
              <!-- /.global-links -->
              </div>
              
              
            </div>
        </div>
          <div class="userlinks">
            <?php // print $usermenu; ?>
            
                          
              
          </div>
        </div>
      </div>
    </div>
  </div>
  
  <div id="topmenu">
    
    <div class="container_12 -clear-block">
      <div class="grid_12">
        <div class="topmenu-content">
          
          <?php if (!empty($spacetitle) && $spacetype == 'og') : ?>
          <div class="group-header alpha omega">
            <h1><?php print $spacetitle; ?></h1>
          </div>

          <div class="tools-menu-container">
    
          <?php print theme('links', $primary_links, array('class' => 'links tools')); ?>
          </div>
          <div class="clear"></div>

          <?php else:?>
            <span class="slogan">Din guide til studenthverdagen!</span>          
          <?php endif; ?>
          
          
          <div class="logo">

            <?php /*
            <a href="<?php print $base_path;?>">
              <img src="<?php print $base_path . 'sites/all/themes/studentparlamentet/images/studparl_logo.png';?>">
            </a>
            */?>
            
          <!-- /.logo -->  
          </div>          
          <?php // print theme('links', $primary_links); ?>
          
        </div>
      </div>
    </div>
  </div>
  
  <?php if ($messages || $help) : ?>

  <div class="container_12">
    <div class="grid_12">
      <?php print $messages; ?>
      <?php print $help; ?>
    </div>
    <div class="clear"></div>
  </div>
  <?php endif; ?>
  
  <?php // if ($is_front && $spacetype !== 'og') : ?>
  
    <?php // include 'includes/frontpage.tpl.php'; ?>
  
  <?php // else : ?>
  
  <div id="page">
    
    <?php print $context_links;?>
    
    
    <div class="container_12">          
      
      <?php if ($top_fullwidth) : ?>
      <div class="grid_12 top-fullwidth">
        <div class="box region"><div class="box-content"><?php print $top_fullwidth; ?></div></div>
      </div>
      
      <div class="clear"></div>
      <?php endif; ?>
      
      <?php if( $top_grid_1 || $top_grid_2 || $top_grid_3) : ?>
      <div class="grid_4 top-grid-1"><div class="box region"><div class="box-content"><?php print $top_grid_1 ? $top_grid_1 : '&nbsp;'; ?></div></div></div>
      <div class="grid_4 top-grid-2"><div class="box region"><div class="box-content"><?php print $top_grid_2 ? $top_grid_2 : '&nbsp;'; ?></div></div></div>
      <div class="grid_4 top-grid-3"><div class="box region"><div class="box-content"><?php print $top_grid_3 ? $top_grid_3 : '&nbsp;'; ?></div></div></div>
      
      <div class="clear"></div>
      <?php endif; ?>
      
      <?php /*
      <?php if ($left) : ?>
      <div class="grid_3 left"><div class="box region"><div class="box-content"><?php print $left; ?></div></div></div>
      <?php endif; ?>
      */ ?>

      <div class="grid_<?php print (12 /*- ($left ? 3 : 0)*/- ($right ? 4 : 0)); ?>">
        <div class="box content"><div class="box-content">
          <?php if ($content_top) : ?>
          <div class="content-top"><div class="box region"><div class="box-content"><?php print $content_top; ?></div></div></div>
          <?php endif; ?>
          
          <?php if ($tabs) : ?>
          <?php print $tabs; ?>
          <?php endif; ?>
          
          <div class="main">
            
            <?php if(!$is_front):?>
              <h1><?php print $title; ?></h1>
            <?php endif; ?>
            
            <?php print $content; ?>
          </div>
          
          <?php if ($content_bottom) : ?>
          <div class="content-bottom"><div class="box region"><div class="box-content"><?php print $content_bottom; ?></div></div></div>
          <?php endif; ?>
        </div></div>
      </div>
      
      <?php if ($right) : ?>
      <div class="grid_4 right"><div class="box region"><div class="box-content"><?php print $right; ?></div></div></div>
      <?php endif; ?>
      
      <div class="clear"></div>
      
      <?php /*
      <?php if ($bottom_grid_1 || $bottom_grid_2 || $bottom_grid_3) : ?>
      <div class="grid_4 bottom-grid-1"><div class="box region"><div class="box-content"><?php print $bottom_grid_1 ? $bottom_grid_1 : '&nbsp;'; ?></div></div></div>
      <div class="grid_4 bottom-grid-2"><div class="box region"><div class="box-content"><?php print $bottom_grid_2 ? $bottom_grid_2 : '&nbsp;'; ?></div></div></div>
      <div class="grid_4 bottom-grid-3"><div class="box region"><div class="box-content"><?php print $bottom_grid_3 ? $bottom_grid_3 : '&nbsp;'; ?></div></div></div>
      
      <div class="clear"></div>
      <?php endif; ?>
      */?>
      
      <?php if ($bottom_fullwidth) : ?>
      <div class="grid_12 bottom-fullwidth">
        <div class="box region"><div class="box-content"><?php print $bottom_fullwidth; ?></div></div>
      </div>
      
      <div class="clear"></div>
      <?php endif; ?>
          
    </div>
    
  </div>
  
  <?php // endif; ?>
  
</div></div>
<!-- end page-wrap -->

<!-- start page footer -->


    <div style="
    background: #d1e4cf;
    width: 100%;
    ">
     
     <div class="container_12">
    
 
     <?php if ($bottom_grid_1 || $bottom_grid_2 || $bottom_grid_3) : ?>
     <div class="grid_4 bottom-grid-1"><div class="box region"><div class="box-content"><?php print $bottom_grid_1 ? $bottom_grid_1 : '&nbsp;'; ?></div></div></div>
     <div class="grid_4 bottom-grid-2"><div class="box region"><div class="box-content"><?php print $bottom_grid_2 ? $bottom_grid_2 : '&nbsp;'; ?></div></div></div>
     <div class="grid_4 bottom-grid-3"><div class="box region"><div class="box-content"><?php print $bottom_grid_3 ? $bottom_grid_3 : '&nbsp;'; ?></div></div></div>
     
     </div>
     <div class="clear"></div>
     <?php endif; ?>
     
     </div>


<!-- end page footer -->
<?php print $closure; ?>
</body>
</html>
