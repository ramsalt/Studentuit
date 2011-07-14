<?php
/*
Author: Roger Howorth
Author URI: http://www.thehypervisor.com
Plugin URI: http://www.thehypervisor.com/simple-facebook-connect-extensions
Description: Adds a PHP function to invite a list of Facebook users to a Facebook event. Requires Simple Facebook Connect plugin by Otto.
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

function sfce_invite_people() {
	$num_args = func_num_args();
	if ( $num_args <> '1' )
		wp_die('You must pass the correct arguments as an array to sfce_invite_group when you invoke the function. See plugin readme for more details.');
	$args = func_get_arg(0);
	$fboptions = get_option('sfc_options');

	// Get OAuth access token from args
//	$access_token = sfce_get_access_token( array( 'app_id' => $fboptions['appid'], 'redirect_uri' => 'http://' . $_SERVER['HTTP_HOST'] . $_SERVER['REQUEST_URI'], 'app_secret' => $fboptions['app_secret'] ));

	$access_token = $args['access_token'];
	if ( !isset($access_token) || $access_token == '' ) wp_die('You must provide an access token on the SFCe Create Event Settings page.');

	if ( $args['group_id'] == '' || $access_token == '' || $args['event_id'] == '' || $args['fb_user'] == '' ) wp_die('Invite people failed because of missing paramter(s).<br>Group Id:' . $args['group_id'] . '<br>Access token:' . $access_token . '<br>Event id:' . $args['event_id'] . '<br>FB User:' . $args['fb_user'] );

	// And invite the people

	if ( isset( $args['group_id'] )) 
		invite_fb_group(array(
                                'access_token' => $access_token
                                ,'eid' => $args['event_id']
                                ,'fb' => $args['fb']
                                ,'gid' => $args['group_id']
				,'fb_user' => $args['fb_user']
        	        ));
	if ( isset( $args['page_id'] ))
		invite_fb_page(array(
                                'access_token' => $access_token
                                ,'eid' => $args['event_id']
                                ,'fb' => $args['fb']
                                ,'pid' => $args['page_id']
				,'fb_user' => $args['fb_user']
        	        ));
}

function invite_fb_page() {
	$num_args = func_num_args();
	if ( $num_args <> '1' )
		wp_die('You must pass the correct arguments as an array to invite_fb_page when you invoke the function. See plugin readme for more details.');
	$args = func_get_arg(0);
	$personal_message = 'Can you help again?';
	$Url = 'https://graph.facebook.com/' . $args['pid'] . '/members';
	$post_data = 'access_token=' . $args['access_token'];
	$members_all = go_curl( array(
				'Url' => $Url
				,'post_data' => $post_data
			));
	wp_die('Members:' . $members_all );
	//$members_all=$args['fb']->api_client->groups_getMembers( $args['gid'] );
	$members = $members_all['members'];
	foreach ($members as $member) {
		if ( $member == $args['fb_user'] ) continue;
		$member_list .= $member . '%2C';
		}
	$member_list = substr($member_list, 0, strlen($member_list) - 3);
	wp_die('Members:' . $member_list);

	$Url = 'https://api.facebook.com/method/events.invite';
	$post_data = 'eid=' . $args['eid'];
	$post_data .= '&uids=' . $member_list;
	$post_data .= '&access_token=' . $args['access_token'];
	$post_data .= '&personal_message=' . $personal_message;

	$output = go_curl( array(
                                'Url' => $Url
				,'post_data' => $post_data
                ));
	 wp_die('Output: ' . $output);
}

function invite_fb_group() {
	$num_args = func_num_args();
	if ( $num_args <> '1' )
		wp_die('You must pass the correct arguments as an array to invite_fb_group when you invoke the function. See plugin readme for more details.');
	$args = func_get_arg(0);

	$personal_message = 'Can you help again?';
	$members_all=$args['fb']->api_client->groups_getMembers( $args['gid'] );
	$members = $members_all['members'];
	foreach ($members as $member) {
		if ( $member == $args['fb_user'] ) continue;
		$member_list .= $member . '%2C';
		}
	$member_list = substr($member_list, 0, strlen($member_list) - 3);

	$Url = 'https://api.facebook.com/method/events.invite';
	$post_data = 'eid=' . $args['eid'];
	$post_data .= '&uids=' . $member_list;
	$post_data .= '&access_token=' . $args['access_token'];
	$post_data .= '&personal_message=' . $personal_message;

	$output = sfce_go_curl( array(
                                'Url' => $Url
				,'post_data' => $post_data
                ));
	// wp_die('Output: ' . $output);
}

function sfce_get_access_token() {
	$num_args = func_num_args();
	if ( $num_args <> '1' )
		wp_die('You must pass the correct arguments as an array to get_app_access_token when you invoke the function. See plugin readme for more details.');
	$args = func_get_arg(0);

	$code = $_REQUEST["code"];
	if(empty($code)) {
        $dialog_url = "http://www.facebook.com/dialog/oauth?client_id=" 
            . $args['app_id'] . "&redirect_uri=" . urlencode($args['redirect_uri']);

        echo("<script> top.location.href='" . $dialog_url . "'</script>");
    }

    $token_url = "https://graph.facebook.com/oauth/access_token?client_id="
        . $args['app_id'] . "&redirect_uri=" . urlencode($args['redirect_uri']) . "&client_secret="
        . $args['app_secret'] . "&code=" . $code;

    $access_token = file_get_contents($token_url);
    $graph_url = "https://graph.facebook.com/me?" . $access_token;

    $user = json_decode(file_get_contents($graph_url));

    wp_die("Hello " . $user->name);


/*
	$Url = 'https://graph.facebook.com/oauth/access_token';
	$post_data = 'client_id=' . $args['app_id'];
	$post_data .= '&client_secret=' . $args['app_secret'];
	$post_data .= '&code=' . $_REQUEST['code'];
	$output = sfce_go_curl( array(
                                'post_data' => $post_data
                                ,'Url' => $Url
                ));
*/
wp_die('Token:' . $access_token);
	return $token[0];
}

function sfce_session_to_access_token() {
	// This doesn't work because the FB function passes its result back on the redirect URL,
	// not via curl
	$num_args = func_num_args();
	if ( $num_args <> '1' )
		wp_die('You must pass the correct arguments as an array to session_to_access_token when you invoke the function. See plugin readme for more details.');
	$args = func_get_arg(0);
	$redirect_uri = "http%3A%2F%2Fwww.lfns.co.uk%2F";
	// Get verification code
	$Url = 'https://graph.facebook.com/oauth/authorize';
	$post_data ='client_id=' . $args['app_id'];
	$post_data .= '&redirect_uri=' . $redirect_uri;
	$verification_code = go_curl( array(
                                'post_data' => $post_data
                                ,'Url' => $Url
                ));
	wp_die('Verification code:' . $verification_code);

	// Use verification code to get access token
	$Url = 'https://graph.facebook.com/oauth/access_token';
	$post_data = 'client_id=' . $args['app_id'];
	$post_data .= '&client_secret=' . $args['app_secret'];
	$post_data .= '&code=' . $verification_code;
	$post_data .= '&redirect_uri=' . $redirect_uri;
	$access_token = go_curl( array(
                                'post_data' => $post_data
                                ,'Url' => $Url
                ));

	wp_die('Access token:' . $access_token);

	// Get access token
	$Url = 'https://graph.facebook.com/oauth/exchange_sessions';
	// type=client_cred&
	$post_data = 'client_id=' . $args['app_id'];
	$post_data .= '&client_secret=' . $args['app_secret'];
	$post_data .= '&sessions=' . $args['session_key'];
	$output = go_curl( array(
                                'post_data' => $post_data
                                ,'Url' => $Url
                ));
	$access_tokens = json_decode( $output, TRUE);
	$temp = $access_tokens[0];
	return $temp;
//	return $output;
}

function sfce_curPageURL() {
 $pageURL = 'http';
 if ($_SERVER["HTTPS"] == "on") {$pageURL .= "s";}
 $pageURL .= "://";
 if ($_SERVER["SERVER_PORT"] != "80") {
  $pageURL .= $_SERVER["SERVER_NAME"].":".$_SERVER["SERVER_PORT"].$_SERVER["REQUEST_URI"];
 } else {
  $pageURL .= $_SERVER["SERVER_NAME"].$_SERVER["REQUEST_URI"];
 }
 return $pageURL;
}

function sfce_go_curl(){
	$num_args = func_num_args();
	if ( $num_args <> '1' )
		wp_die('You must pass the correct arguments as an array to go_curl when you invoke the function. See plugin readme for more details.');
	$args = func_get_arg(0);
	$ch = curl_init();
	// set URL to download
	curl_setopt($ch, CURLOPT_URL, $args['Url']);
	// set POST data
	curl_setopt($ch, CURLOPT_POSTFIELDS, $args['post_data']);
 	// set referer:
	curl_setopt($ch, CURLOPT_REFERER, "http://www.lfns.co.uk/");
	// user agent:
	curl_setopt($ch, CURLOPT_USERAGENT, "RozillaXYZ/1.0");
	// remove header? 0 = yes, 1 = no
	curl_setopt($ch, CURLOPT_HEADER, 0);
	// should curl return or print the data? true = return, false = print
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
	// timeout in seconds
	curl_setopt($ch, CURLOPT_TIMEOUT, 20);
	// download the given URL, and return output
	$output = curl_exec($ch);
	// close the curl resource, and free system resources
	curl_close($ch);
	return $output;
}
?>
