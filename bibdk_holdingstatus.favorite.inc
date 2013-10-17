<?php

/*
 * get AgencyInformation from favourites
 */
function bibdk_holdingstatus_get_agency_information($favourites){
  if ( !empty($favourites) )
  {
    foreach($favourites as $agencyId => $favourite){
      $information = $favourite->getInformation();
      if (isset($information)){
        $return[$information->getAgencyId()] = $information;
      }
    }
    return isset($return) ? $return : null;
  }
  return null;
}

/** implements hook_ting_openformat_actions
 * @param $type
 * @param $entity
 * @param $view_mode
 * @param $langcode
 * @return mixed
 */
function bibdk_holdingstatus_ting_openformat_actions($type, $entity, $view_mode, $langcode){
  if ($type == 'bibdkManifestation'){
    $actions['favourite_holdings'] = array(
      '#markup' => bibdk_holdingstatus_holdings_for_favourites_view($entity->id),
      '#weight' => 1,
    );
    return $actions;
  }
}

/** generate view for favourite holdings
 * @param $pid
 * @return string
 */
function bibdk_holdingstatus_holdings_for_favourites_view($pid){
   $item_list = _bibdk_holdingsstatus_favourite_item_list($pid);

  if (empty($item_list)) {
    return;
  }

  $fav['link_text'] = t('home_at_favourites');
  $fav['path'] = 'favourites';
  $fav['favourites'] = array(
    '#theme' => 'item_list',
    '#items' => $item_list,
    '#attributes' => array(
      'class' => array('favourite-list', 'form-item'),
    ),
    '#attached' => array(
      'js' => array(drupal_get_path('module', 'bibdk_holdingstatus') . '/js/bibdk_holdingstatus.js'),
    ),
  );

  return theme('bibdk_holdings_manifestation_field', $fav);
}


/** Helper function - generate item list for favourite holdings
 * @param $pid
 * @param $information
 * @return array
 */
function _bibdk_holdingsstatus_favourite_item_list($pid) {
  $favourites = bibdk_favourite_get_favourites();
  $item_list = array();
  foreach ($favourites as $key => $favourite) {
    $lookupUrl = $favourite->getInformation()->getLookupUrl();
    $item_list[] = theme('favourite_holdings', array(
      'library_name' => $favourite->getInformation()->getAgencyName(),
      'lid' => $key,
      'pid' => $pid,
      'link' => (strpos($lookupUrl, '_IDNR_') !== false) ? str_replace('_IDNR_', $localIdentifier, $lookupUrl) : $lookupUrl . $localIdentifier,
    ));
  }

  return $item_list;
}
