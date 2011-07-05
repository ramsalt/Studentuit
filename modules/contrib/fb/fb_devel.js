/**
 * Devel helpers and sanity checks.
 *
 * This file will be included only when fb_devel.module is enabled and user
 * has 'access devel information' permission.
 */

FB_Devel = function(){};

/**
 * Called when fb.js triggers the 'fb_init' event.
 */
FB_Devel.initHandler = function() {
  //alert("FB_Devel.initHandler");
  if (typeof(FB) != 'undefined' &&
      (!Drupal.settings.fb || FB._apiKey != Drupal.settings.fb.fb_init_settings.appId)) {
    // We reach this code if there is a <script> tag initializing Facebook's
    // Javascript before fb.js has a chance to initilize it!

    //alert("fb_devel.js: Facebook JS SDK initialized badly."); // verbose
    debugger; // not verbose.
  }
};

// Helper, for debugging facebook events.
FB_JS.debugHandler = function(response) {
  debugger;
};

/**
 * Implements Drupal javascript behaviors.
 */
Drupal.behaviors.fb_devel = function(context) {
  jQuery(document).bind('fb_init', FB_Devel.initHandler);

  // Facebook events that may be of interest...
  //FB.Event.subscribe('auth.login', FB_Devel.debugHandler);
  //FB.Event.subscribe('auth.logout', FB_Devel.debugHandler);
  //FB.Event.subscribe('auth.statusChange', FB_Devel.debugHandler);
  //FB.Event.subscribe('auth.sessionChange', FB_Devel.debugHandler);

};