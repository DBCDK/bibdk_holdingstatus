<?php


/**
 * Implements hook_show_manifestation_info_prerender
 */
function bibdk_holdingstatus_show_manifestation_info_prerender($ids, $uid){
  $favourites = _bibdk_favourite_get_from_webservice();
  if (!isset($favourites) || count($favourites) == 0)
    return;
  $localizations = open_holdingstatus_localisationRequest($ids);
  foreach($localizations['agencies'] as $lid => $holdings){
    foreach($holdings['holdings'] as $pid => $holding){
      BibdkHoldings::setHoldings($holding, $pid, $lid);
    }
  }
  $information = bibdk_holdingstatus_get_agency_information($favourites);
  BibdkHoldings::setAgencyInformation($information);
}

function bibdk_holdingstatus_get_holdings_for_favorites($pid, $informations){
  if ( !empty($informations) )
  {
    foreach($informations as $agencyId => $information){
        $holding = BibdkHoldings::getHoldings($pid, $information->getAgencyId());
        if (isset($holding)){
          $return[$agencyId] = array(
            'holding' => $holding,
            'information' => $information,
          );
        }
    }
    return isset($return) ? $return : null;
  }
  return null;
}

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
  $information = BibdkHoldings::getAgencyInformation();
  if (!isset($information))
    return;

   $item_list = _bibdk_holdingsstatus_favourite_item_list($pid, $information);

  if (!isset($item_list))
    return;

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
function _bibdk_holdingsstatus_favourite_item_list($pid, $information) {
  $item_favourites = bibdk_holdingstatus_get_holdings_for_favorites($pid, $information);

  if (!isset($item_favourites)) {
    return;
  }

  $item_list = array();
  foreach ($item_favourites as $key => $favourite) {
    $lookupUrl = $favourite['information']->getLookupUrl();
    $localIdentifier = $favourite['holding']['localIdentifier'];
    $item_list[] = theme('favourite_holdings', array(
      'library_name' => $favourite['information']->getAgencyName(),
      'lid' => $key,
      'pid' => $pid,
      'link' => (strpos($lookupUrl, '_IDNR_') !== false) ? str_replace('_IDNR_', $localIdentifier, $lookupUrl) : $lookupUrl . $localIdentifier,
    ));
  }

  return $item_list;
}
