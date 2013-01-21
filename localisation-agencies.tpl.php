
<div id="<?php $agencies['branchId'] ?>" class="localisation-agency">
<?php if ( $agencies['branchName'] != $agencies['agencyName']) { ?>
  <p class="branchName"><?php print $agencies['branchName']; ?></p>
<?php } ?>
  <p class="agencyName"><?php print $agencies['agencyName']; ?></p>
  <p class="postalAddress"><?php print $agencies['postalAddress']; ?></p>
  <p class="postalCode"><?php print $agencies['postalCode']; ?></p>
  <p class="city"><?php print $agencies['city']; ?></p>
  <p class="holdings visuallyhidden"></p>
  <p class="lookupUrl"><?php echo drupal_render($agencies['lookupUrl']); ?></p>
<?php if ( !empty($agencies['note']) ) { ?>
  <p class="note"><?php print $agencies['note']; ?></p>
<?php } ?>
<?php if ( isset($agencies['error']) ) { ?>
  <p class="note"><?php print $agencies['error']; ?></p>
<?php } ?>
</div>
