Drupal.behaviors.bannerMenu = function(context){
var admin = $('#spaces-navigation-admin').find('.spaces-admin');
var adminsub = $('#spaces-navigation-admin-sub');
//adminsub.css({top:admin.height()});
admin.click(function(){
admin.parent().toggleClass('open');
adminsub.toggleClass('open');
hover = false;
$(this).parent().hover(function(){
hover = true;
}, function(){
hover = false;
});
$(document.body).click(function(){
if(!hover) {
admin.parent().removeClass('open');
adminsub.removeClass('open');
}
});
// abort anchor click
return false;
});
} 