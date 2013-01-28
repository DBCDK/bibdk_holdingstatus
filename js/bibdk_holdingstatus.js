(function ($) {

    /** Insert holding status */
    Drupal.addHoldingStatus = function (holdingstatus) {
        $('.holding-status-load[data-pid=' + holdingstatus.pid + '][data-lid=' + holdingstatus.lid + ']').replaceWith(holdingstatus.data);
    },

    /** Get holdingstatus via ajax */
    Drupal.behaviors.holdingsstatus = {

        attach:function (context) {
            $('.holding-status-load', context).each(function (i, element) {
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
            });
        },
        detach:function (context) {

        }
    };

}(jQuery));

