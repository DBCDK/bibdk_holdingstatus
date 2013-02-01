<div id="<?php print $branchId ?>" class="localisation-agency">
<?php if ( $branchName != $agencyName ) { ?>
  <p class="branchName"><?php print $branchName; ?></p>
<?php } ?>
  <p class="agencyName"><?php print $agencyName; ?></p>
  <p class="postalAddress"><?php print $postalAddress; ?></p>
  <p class="postalCode"><?php print $postalCode; ?></p>
  <p class="city"><?php print $city; ?></p>
  <?php echo drupal_render($lookupUrl); ?>
  <p class="note"><?php print $note; ?></p>
  <p class="note"><?php print $error; ?></p>
</div>
