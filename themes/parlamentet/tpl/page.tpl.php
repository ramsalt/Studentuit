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
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
  <script type="text/javascript"><?php /* Needed to avoid Flash of Unstyled Content in IE */ ?> </script>

<style>

body {
  font-family: "helvetica neue";
  font-size: 85%;
  background: #eee;
  line-height: 1.3em;
}

div.top-container {
/*  background: #d1e4cf; */ 
  background: #4287cc;
  border-bottom: solid 1px gray;  
}

div.top, div.grouptop, div.content-container, div.groupmenu {
  width: 960px;
  margin: 0 auto;
}

div.inner {
  padding: 20px;
}

div.top {
  height: 35px;
}

div.logo {
  background: white;
  float: left;
  padding: 10px;
  border-bottom: solid 1px gray;
  border-left: solid 1px gray;
  border-right: solid 1px gray;
}

div.user {
  float: right;
}

div.top ul.menu {
  float: right;
  font-size: 80%;
  list-style-type: none;
  display: inline;
  text-transform: uppercase;
  padding: 10px 0 10px 10px;
}

div.top ul.menu a {
  text-decoration: none;
}

div.top ul.menu li {
  display: inline;
  color: black;  
}

div.top ul.menu li a {
  background: #a9cdf2;
  color: black;
  padding: 3px;  
  -moz-border-radius: 3px;
  -webkit-border-radius: 3px;
}

div.top ul.menu li a.active  {
  display: inline;  
  background: #eee;  
  padding: 3px;
  -moz-border-radius: 3px;
  -webkit-border-radius: 3px;
}

div.grouptop {
  border-bottom: solid 2px #4287cc;
  display: table;
}

div.grouptitle {
  background: #4287cc;
  color: white;
  float: right;
  padding: 10px;
  text-align: right;
  width: 320px;
}

div.grouptitle a {
  color: white;
  text-decoration: none;
}

div.groupmenu {
  padding: 10px 0;
}

div.groupmenu a {
  color: black;
  text-decoration: none;
}

div.groupmenu a.active {
  background: #4287cc;
  color: white;
  padding: 2px 4px;
  text-decoration: none;
  -moz-border-radius: 3px;
  -webkit-border-radius: 3px;  
}

div.content-container {
  clear: both;
  display: table;
  margin-top: 60px;
  background: white;
/*  border: solid 1px gray; */ 
}

div.main-content {
  float: left;
  width: 580px;
}

div.region-right {
  float: right;
  width: 320px;
}

a {
  color: #4287cc;
  text-decoration: none;
}

h1, h2, h3 {
  font-size: 140%;
}

p {
  margin-bottom: 1.2em;
}

div.meta {
  color: gray;
  font-size: 90%;
  text-align: right;
  margin-bottom: 10px;
}

</style>

</head>
<body class="<?php print $body_classes; ?>">

<div class="top-container">
  <div class="top">
  
    <div class="logo">
  
      <a href="<?php print $front_page ?>" title="<?php print t('Home'); ?>" rel="home">
        <img src="<?php print $base_path . 'sites/all/themes/parlamentet/img/studentparlamentet_logo.png';?>">
      </a>
      
    <!-- /.logo -->  
    </div>
  
      
      <div class="user">
      
        <?php // henter ut global-menyen 
        $block = module_invoke('menu', 'block', 'view', 'menu-global');
        print $block['content'];
        ?>
        
        <?php /*<img src="<?php print $base_path . 'sites/all/themes/parlamentet/img/fb-conn.png';?>">*/?>
      <!-- /.user -->
      </div>
    </div>
    <!-- /.top -->
  </div>
<!-- /.top-container -->
</div>



<div class="content-container">

  <?php if(spaces_get_space() && $spacetype == 'og'): ?>
    <div class="grouptop">
    <div class="grouptitle">
      <h1><?php print $spacetitle; ?></h1>
    <!-- /.grouptitle -->
    </div>
    <div class="groupmenu">
      <?php if (!empty($primary_links)): ?>
        <?php print theme('links', $primary_links, array('class' => 'links primary-links')); ?>
      <?php endif; ?>

      <?php if (!empty($secondary_links)): ?>
        <?php print theme('links', $secondary_links, array('class' => 'links secondary-links')); ?>
      <?php endif; ?>    
    <!-- /.groupmenu -->
    </div>
    <!-- /.grouptop -->
    </div>  
  <?php endif;?>

  <div class="inner">
  <div class="main-content">
    <?php if (!empty($title)): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
    <?php if (!empty($tabs)): ?><div class="tabs"><?php print $tabs; ?></div><?php endif; ?>
    <?php if (!empty($messages)): print $messages; endif; ?>
    <?php if (!empty($help)): print $help; endif; ?>

    <?php print $content; ?>
  <!-- /. main-content -->  
  </div>

    <?php if ($right) : ?>
      <div class="region-right"><?php print $right; ?></div>
    <?php endif; ?> 
    </div>

<!-- /.content-container -->
</div>



  <?php // print $feed_icons; ?>
  <?php print $closure; ?>

  </div> <!-- /page -->

</body>
</html>
