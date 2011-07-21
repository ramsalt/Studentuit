(function( $ ){
  $.fn.viewslinks = function() {
    this.parents('.view').each(function(){
      console.log($(this).position());
    });
  };
})( jQuery );

$(document).ready(function(){
  $('.views-admin-links').viewslinks();
  
  /*
  $('#fpslider').nivoSlider({
    effect: 'random',
    prevText: 'Forrige',
    nextText: 'Neste',
    controlNav: false,
    pauseTime: 5000,
  });
  */
  
});
