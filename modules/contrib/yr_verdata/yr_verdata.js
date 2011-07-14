
// Enable tabs on the forecast page for a single location.
Drupal.behaviors.yr_verdataTabs = function (context) {
  // Move the list used for tab-nav out of the div, or the tabs won't work.
  $("#yr-content").prepend($("#yr-content>.item-list>ul"));
  // Remove the useless div.
  $("#yr-content>.item-list").remove();
  // Add the tabs.
  try{
    if ($.ui.version.match('1.7') || $.ui.version.match('1.8')) { // Modern, for those using jquery_update module.
      $("#yr-content").tabs();
    }
    if ($.ui.version.match('1.6')) { // Not so modern.
      $("#yr-content > ul").tabs();
    }
  }catch(e){
    
  }

}