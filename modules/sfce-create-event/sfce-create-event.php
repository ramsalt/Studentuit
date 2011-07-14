<?php
/*
Plugin Name: SFCe - Create Event
Version: 3.96.1
Author: Roger Howorth
Author URI: http://www.thehypervisor.com
Plugin URI: http://www.thehypervisor.com/simple-facebook-connect-extensions
Description: Adds a PHP function to create a Facebook event. Requires Simple Facebook Connect plugin by Otto.
License: http://www.gnu.org/licenses/gpl.html

Copyright (c) 2011 Roger Howorth

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

include_once('sfce-invite-people.php');

add_action("plugins_loaded", "sfce_create_event_init");
add_action("admin_menu", "sfce_create_event_init");

function sfce_create_event_init() {
	$plugin_dir = dirname(plugin_basename(__FILE__));
	load_plugin_textdomain( 'sfce-create-event', null, $plugin_dir . '/languages/');
	return;
}

include_once('sfce_create_event_post.php');
include_once('sfce-settings-page.php');

function sfce_create_event() {
	// See Notes section for possible arguments - http://wiki.developers.facebook.com/index.php/Events.create
	$num_args = func_num_args();
	if ( $num_args <> '1' )
		wp_die(__('You must pass the correct arguments as an array to sfce_create_event when you invoke the function. See plugin readme for more details.', 'sfce-create-event'));
	$args = func_get_arg(0);
	// Make Facebook event
		// Check if the post is published before creating fb event, disable this line for testing
	//	if ( $args['post_id']->post_status == "draft" ) return $args['post_id'];

		// load Facebook platform
		$fboptions = get_option('sfc_options');
		$options = get_option('sfce_event_options');

		include_once WP_PLUGIN_DIR . '/simple-facebook-connect/facebook-platform/facebook.php';
		$fb=new Facebook($fboptions['api_key'], $fboptions['app_secret']);
		$fb_user = $fb->user;
		if ( empty ($fb_user)) {
			//$about = $fb->api_client->users_getInfo($fb_user,'about_me');
			// Not loggged into FB so don't create an event
			return $args['post_id'];
		} 

		if(!$fb->api_client->users_hasAppPermission('create_event')) { 
			echo'<script type="text/javascript">window.open("http://www.facebook.com/authorize.php?api_key='.$fb->api_key.'&v=1.0&ext_perm=create_event", "Permission");</script>';
			// echo'<meta http-equiv="refresh" content="0; URL=javascript:history.back();">';
			wp_die(__('You should have seen a new Facebook window asking if you "Allow Events from [your Facebook page]". This tells Facebook it\'s OK for you to create events on your page. You should grant permission, then return here, press your browser back button and try again.', 'sfce-create-event'));
		} 

		$start_time=mktime($args['start_hour'],$args['start_min'],"00",$args['month'],$args['day'],$args['year']);
		$start_time = substr(date('c',$start_time),0,16);

		$end_time=mktime($args['end_hour'],$args['end_min'],"00",$args['month'],$args['day'],$args['year']);
		$end_time = substr(date('c',$end_time),0,16);

	// Add promo link if ok
	$options = get_option('sfce_event_options');
	if ( $options['sfce_show_promo'] ) $args['description'] .= "\nAuto event creation by http://www.thehypervisor.com";

		$event_fb = array("name"=>$args['name'], "host"=>$args['host'], "start_time"=>$start_time, "end_time"=>$end_time,  "description"=>$args['description'], "tagline"=>$args['tagline']);
		if ( $args['is_fanpage'] == 'TRUE' ) $event_fb['page_id'] = $fboptions['fanpage']; else if ( $args['is_fanpage'] && $args['page_id'] <> '' ) $event_fb['page_id'] = $args['page_id'];
	
		if ( $args['privacy'] ) $event_fb['privacy_type'] = $args['privacy'];
		$event_fb = array_map(utf8_encode, $event_fb); 

		try{
			$event_id=$fb->api_client->events_create(json_encode( $event_fb ), $args['photo']);
			/* echo'<meta http-equiv="refresh" content="0; URL=">'; */
		} catch(Exception $e) {
			if ( $e->getCode() == '200' ) {
				// update_post_meta ( $post_id, 'fb_event', 'created' );
				wp_die(__('You must be an administrator of your Facebook page in order to create events. Please ask an existing Facebook page admin to fix this for you. Other details have been saved, press your browser "Back" button and carry on!', 'sfce-create-event'));
			}
			echo 'Error message: '.$e->getMessage().' Error code:'.$e->getCode();
		} 
	// Invite people?
	if ( $args['group_id'] <> '') {
		$invite_ok = sfce_invite_people( array(
		'app_id' => $fboptions['appid']
		,'app_secret' => $fboptions['app_secret']
		,'fb' => $fb
		,'group_id' => $args['group_id']
		,'event_id' => $event_id
		,'fb_user' => $fb_user
		,'access_token' => $options['sfce_access_token']
		));
	}
	if ( $args['invite_page'] <> '' ) {
		$invite_ok = sfce_invite_people( array(
		'app_id' => $fboptions['appid']
		,'app_secret' => $fboptions['app_secret']
		,'fb' => $fb
		,'page_id' => $args['invite_page']
		,'event_id' => $event_id
		,'fb_user' => $fb_user
		,'access_token' => $options['sfce_access_token']
		));
	}

	return $event_id;
} //end sfce_create_event
