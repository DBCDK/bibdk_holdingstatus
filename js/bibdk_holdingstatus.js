(function ($) {

    /** Insert holding status */
    Drupal.addHoldingStatus = function (holdingstatus) {
        $('.holding-status-load[data-pid=' + holdingstatus.pid + '][data-lid=' + holdingstatus.lid + ']').replaceWith(holdingstatus.data);
    },
    Drupal.loadHoldingStatus = function(element){
        var pid = $(element).attr('data-pid');
        var lid = $(element).attr('data-lid');
        /* Add throbber*/
        $(element).addClass('ajax-progress');
        $(element).html('<span class="throbber">&nbsp;</span>');

        /* Call ajax */
        var request = $.ajax({
            url:Drupal.settings.basePath + 'holdings/status',
            type:'POST',
            data:{
                pid:pid,
                lid:lid
            },
            dataType:'json',
            success:Drupal.addHoldingStatus
        });
    }
    /** Get holdingstatus via ajax */
    Drupal.behaviors.holdingsstatus = {

        attach:function (context) {
            $('.holding-status-load', context).each(function (i, element) {
                Drupal.loadHoldingStatus(element);
            });
            $('.load-holdings', context).click(function(e){
                $('.popover').addClass('visuallyhidden');
                $(this).siblings().find('.holding-status-element').each(function (i, element) {
                    $(element).removeClass('holding-status-element').addClass('holding-status-load');
                    Drupal.loadHoldingStatus(element);
                });
            });

        },
        detach:function (context) {

        }
    };

}(jQuery));

