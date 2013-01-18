
<div id="<?php $agencies['branchId'] ?>" class="localisation-agency">
  <p class="agencyName"><?php print $agencies['agencyName']; ?></p>
  <p class="branchName"><?php print $agencies['branchName']; ?></p>
  <p class="postalAddress"><?php print $agencies['postalAddress']; ?></p>
  <p class="postalCode"><?php print $agencies['postalCode']; ?></p>
  <p class="city"><?php print $agencies['city']; ?></p>
  <p class="holdings visuallyhidden"></p>
  <p class="lookupUrl"><?php echo drupal_render($agencies['lookupUrl']); ?></p>
</div>
