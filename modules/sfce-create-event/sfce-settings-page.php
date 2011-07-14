<?php

// Hook for adding admin menus
add_action('admin_menu', 'sfce_event_settings_menu');

// action function for above hook
function sfce_event_settings_menu() {
	add_management_page('Create Facebook Events', 'Create Facebook Events', 8, 'sfce_event_settings_page', 'sfce_event_settings_page');
}


// displays the page content for the admin submenu
function sfce_event_settings_page() {
	global $sfce_text_inputs;

	if ( isset ($_POST['sfce_submit']) )
	{
		if ( !wp_verify_nonce ( $_POST['verify-key'], 'sfce_event') ) die(__('Failed security check. Reload page and retry', 'sfce-create-event'));
		if ( $_POST['sfce_event_privacy_visible'] && ( $_POST['sfce_event_privacy'] <> 'OPEN' && $_POST['sfce_event_privacy'] <> 'CLOSED' )) $error .= 'You must provide a Privacy setting if you want to hide this option. Acceptable settings are OPEN or CLOSED.<p>';
		if ( $_POST['sfce_event_start_hour_visible'] && $_POST['sfce_event_start_hour'] == '' ) $error .= 'You must provide a Start Hour if you want to hide this option.<p>';
		if ( $_POST['sfce_event_start_min_visible'] && $_POST['sfce_event_start_min'] == '' ) $error .= 'You must provide a Start Minute if you want to hide this option.<p>';
		if ( $_POST['sfce_event_end_hour_visible'] && $_POST['sfce_event_end_hour'] == '' ) $error .= 'You must provide an End Hour if you want to hide this option.<p>';
		if ( $_POST['sfce_event_end_min_visible'] && $_POST['sfce_event_end_min'] == '' ) $error .= 'You must provide an End Minute if you want to hide this option.<p>';
		if ( $_POST['sfce_event_name_visible'] && $_POST['sfce_event_name'] == '' ) $error .= 'You must provide a Name of Event if you want to hide this option.<p>';
		if ( !$error )
		{
			foreach( $sfce_text_inputs as $input )
			{
				$options[$input['name']] = stripslashes($_POST[$input['name']]);
				$options[$input['name'] . '_visible'] = $_POST[$input['name'] . '_visible'];
			}
			$options['sfce_hide_postpanel'] = $_POST['sfce_hide_postpanel'];
			$options['sfce_show_promo'] = $_POST['sfce_show_promo'];
			$options['sfce_access_token'] = $_POST['sfce_access_token'];
			$options['sfce_group_id'] = $_POST['sfce_group_id'];

			update_option('sfce_event_options', $options);
			echo '<div id="message" class="updated fade"><p><strong>';
			_e('Facebook Event options updated.', 'sfce-create-event');
			echo '</strong></p></div>';
		}
		else
		{
			echo '<div id="message" class="updated fade"><p><strong>';
			printf(__('%s', 'sfce-create-event'), $error);
			echo '</strong></p></div>';
		}
	} // end if isset
	$options = get_option('sfce_event_options');
	?>
	<form name="form1" method="post" action="<?php echo str_replace( '%7E', '~', $_SERVER['REQUEST_URI']); ?>">
	<div class="form-field">
	<?php
	echo '<h2>';
	_e('Create Facebook Event Configuration', 'sfce-create-event');
	echo '</h2>';
	echo '<input type="hidden" name="verify-key" value="' . wp_create_nonce('sfce_event') . '" />';



	echo "<h3>";
	_e('Default values for new events', 'sfce-create-event');
	echo '</h3>';
	echo '<table style="text-align: left;">';
	echo '<th>';
	_e('Option', 'sfce-create-event');
	echo '</th><th>';
	_e('Value', 'sfce-create-event');
	echo '</th><th>';
	_e('Hide when editing post', 'sfce-create-event');
	echo '?</th>';
	foreach ( $sfce_text_inputs as $input )
	{
		echo '<tr><td><label for="' . $input['label'] . '">';
		printf(__('%s', 'sfce-create-event'), $input['label']);
		echo '</td><td><input type="text" name="' . $input['name'] . '" size="' . $input['size'] . '" maxlength="' . $input['maxlength'] . '" title="';
		printf(__('%s', 'sfce-create-event'), $input['title']);
		echo '" value="';
		echo $options[$input['name']];
		echo '" />';
		echo '</label></td>';
		echo '<td><input type="checkbox"';
		echo ' name="'. $input['name'] . '_visible"';
		if ( $options[$input['name'] . '_visible'] ) echo ' checked="checked"';
		echo ' /></td>';
		echo '</tr>';
	}
	echo '</table>';

	echo "<h3>";
	_e('Disable Create Facebook Events panel when editing posts?', 'sfce-create-event');
	echo '</h3>';
	echo '<table><tr><td width="500">';
	_e('If you call sfce_create_events() directly from your site\'s PHP you can tick this box to deactivate the Create Facebook Events panel in the Wordpress post editor.', 'sfce-create-event');
	echo '</td>';
	echo '<td width="220"><input type="checkbox"';
	echo ' name="sfce_hide_postpanel"';
	if ( $options['sfce_hide_postpanel'] ) echo ' checked="checked"';
	echo ' title="';
	_e('Click here to deactivate Create Facebook Event post editor panel', 'sfce-create-event');
	echo '." /></td></tr></table>';

	echo "<h3>";
	_e('Show link to The Hypervisor?', 'sfce-create-event');
	echo '</h3>';
	echo '<table><tr><td width="500">';
	_e('If you like this plugin I\'d be grateful if you leave a link to ', 'sfce-create-event');
	echo '<a href="http://www.thehypervisor.com">The Hypervisor</a>';
	_e (' at the bottom of your event description. If you don\'t want this link tick this box and it won\'t be added.', 'sfce-create-event');
	echo '</td>';
	echo '<td width="220"><input type="checkbox"';
	echo ' name="sfce_show_promo"';
	if ( $options['sfce_show_promo'] ) echo ' checked="checked"';
	echo ' title="';
	_e('Click here to hide link to The Hypervisor in your events', 'sfce-create-event');
	echo '." /></td></tr></table>';

	echo "<h3>";
	_e('Access Token', 'sfce-create-event');
	echo '</h3>';
	echo '<table><tr><td width="500">';
	_e('In order to invite members of a Facebook group to events you need to enter your Facebook access token here. If you use this feature, be careful who you allow to edit or use the plugin because your access token should be kept private. If you want to cancel an access token, change your Facebook password.', 'sfce-create-event');
	echo '</td>';
	echo '<td width="220"><input type="password"';
	echo ' name="sfce_access_token" ';
	echo 'title="';
	_e('Put a Facebook Access Token here, it should be from an account that has access to the Facebook Group you enter in the box below.', 'sfce-create-event');
	echo '"';
	echo ' value="';
	if ( $options['sfce_access_token'] ) echo $options['sfce_access_token'];
	echo '" /></td></tr></table>';

	echo "<h3>";
	_e('Group ID', 'sfce-create-event');
	echo '</h3>';
	echo '<table><tr><td width="500">';
	_e('The Facebook Group ID. All members of this group will automatically be invited to events.', 'sfce-create-event');
	echo '</td>';
	echo '<td width="220"><input type="text"';
	echo ' name="sfce_group_id" ';
	echo 'title="';
	_e('Put you Facebook Group ID here, it is used only to invite group members to events created with this plugin.', 'sfce-create-event');
	echo '"';
	echo ' value="';
	if ( $options['sfce_group_id'] ) echo $options['sfce_group_id'];
	echo '" /></td></tr></table>';

	?><p class="submit">
	<input type="submit" name="sfce_submit" value="<?php _e('Submit!', 'sfce-create-event'); ?>" />
	</p><br />
	<h3><?php _e('Like this plugin?', 'sfce-create-event'); ?></h3>
	<?php _e('Please visit my website ', 'sfce-create-event') ?><a href="http://www.thehypervisor.com">The Hypervisor</a>
	</div>
	</form>
	<?php _e('Or buy me a beer', 'sfce-create-event') ?>?<br />
	<form action="https://www.paypal.com/cgi-bin/webscr" method="post">
	<input type="hidden" name="cmd" value="_s-xclick" />
	<input type="hidden" name="encrypted" value="-----BEGIN PKCS7-----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-----END PKCS7-----
	" />
	<input type="image" src="https://www.paypal.com/en_US/GB/i/btn/btn_donateCC_LG.gif" name="submit" alt="PayPal - <?php _e('The safer, easier way to pay online','sfce_create_event'); ?>." />
	<img alt="" border="0" src="https://www.paypal.com/en_GB/i/scr/pixel.gif" width="1" height="1" />
	</form>
	<?php
}
