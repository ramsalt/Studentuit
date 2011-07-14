=== Plugin Name ===
Plugin name: SFCe Create Event
Contributors: roggie
Donate link: http://www.rogerh.com/donate.html
Tags: Simple Facebook Connect, Facebook, event, SFC, create
Requires at least: 2.7
Tested up to: 3.1.3
Stable tag:3.96.1

Create Facebook events automatically when you create Wordpress posts. This plugin requires the Simple Facebook Connect plugin by Otto.

== Description ==

This plugin creates events in personal Facebook profiles and Facebook Pages.

To create a Facebook event with this plugin, create or edit a post, scroll down the page to the Create Facebook Event section, fill in the event title and start time, tick the Create Public Facebook Event box and Update or Publish your post.

Provided you are "Connected to Facebook" using the SFC plugin, an event will be created in your Facebook profile or your Facebook Page. If you are not "Connected to Facebook" when you try to create an event, the plugin does nothing. The plugin handles Facebook security properly. The first time you use this plugin, Facebook will ask you to authorize this plugin.

Example: We use this plugin to automatically create public Facebook events for our fan page when certain types of post are published. We also use it to create private Facebook events when other types of post are published.

 
<a href="http://www.thehypervisor.com/simple-facebook-connect-extensions">Changelog</a>

<a href="http://www.facebook.com/home.php?sk=lf#!/pages/The-Hypervisor/114689115238103">Follow me on Facebook</a href>

<a href="http://twitter.com/thehypervisor">Follow me on Twitter</a href>

== Installation ==

This plugin requires Otto's Simple Facebook Connect (SFC) plugin is also installed in your WordPress site. Otto's SFC is an excellent set of plugins for integrating Facebook with your Wordpress site. Unfortunately Otto's SFC does not create Facebook Events. However, this plugin is designed and tested to work with Otto's SFC, so if you want to create Facebook events from your Wordpress blog, install Otto's SFC and this plugin.

1. Install and configure Simple Facebook Connect by Otto.
2. Ensure your Wordpress account is 'connected' to your Facebook account using Otto's Simple Facebook Connect.
3. Unzip the sfce-create-event.zip in your Wordpress plugins directory.
4. Login to WordPress as an administrator, go to Plugins and Activate SFCe Create Events.
5. Create or edit a Post, scroll down and use the Create Facebook Events section to supply information about your Facbook event.

== Frequently Asked Questions ==

<strong>I want to create an event using this plugin but without filling in the form on my Edit Post page. How do I create an array containing the event date/time etc?</strong>
There are several methods of doing this. We use the one below. Please note, in this example we pass some parameters as literal text (e.g. end_min). We pass other parameters as PHP variables (e.g. end_hour). And others we pass as data obtained from an HTML form (e.g. month):

if (function_exists('sfce_create_event')) sfce_create_event( array(
				'name' => $name,
				'description' => $fbdescription,
				'host' => $host,
				'post_id' => $post_id,
				'tagline' => 'Let\'s Skate Together!',
				'is_fanpage' => TRUE,
				'privacy' => 'OPEN',
				'timezone' => 'Europe/London',
				'day' => $_POST['eday'],
				'month' => $_POST['emonth'],
				'year' => $_POST['eyear'],
				'start_hour' => $start_hour,
				'start_min' => '45',
				'end_hour' => $end_hour,
				'end_min' => '00')
				);

Note: Many parameters are optional, see the Facebook documentation (below) for a list of the required paramters.

<strong>Where is the Facebook documentation for creating events in this way?</strong>
http://wiki.developers.facebook.com/index.php/Events.create

== Changelog ==

Click this link to see the <a href="http://www.thehypervisor.com/simple-facebook-connect-extensions">changelog</a>.

== Screenshots ==

1. Section added to "New Post" and "Edit Post" to supply details about your event.
2. Settings page.
