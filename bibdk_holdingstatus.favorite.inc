<?php


/**
 * Implements hook_show_manifestation_info_prerender
 */
function bibdk_holdingstatus_show_manifestation_info_prerender($ids, $uid){
  $localizations = open_holdingstatus_localisationRequest($ids);
  foreach($localizations['agencies'] as $lid => $holdings){
    foreach($holdings['holdings'] as $pid => $holding){
      BibdkHoldings::setHoldings($holding, $pid, $lid);
    }
  }
}

function bibdk_holdingstatus_get_favorites($pid){
  global $user;
  $favourites = _bibdk_favourite_get_from_webservice();
  if ( !empty($favourites) )
  {
    foreach($favourites as $agencyId => $favourite){
        $holding = BibdkHoldings::getHoldings($pid, $agencyId);
        if (isset($holding)){
          $return[$agencyId] = array(
            'holding' => $holding,
            'information' => $favourite->getInformation(),
          );
        }
    }
    return $return;
  }
  return null;
}


/**
 * Implements hook_field_info().
 */
function bibdk_holdingstatus_field_info() {
  return array(
    'bibdk_holdingstatus_favourite' => array(
      'label' => t('Home at favourite.'),
      'description' => t('check status of material at favourite library'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_holdingstatus_favourite_default',
      'no_ui' => TRUE,
    ),
  );
}

/**
 * Implements hook_field_load().
 */
function bibdk_holdingstatus_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {

  foreach ($entities as $id => $entity) {
    $items[$id][]['favourite'] = bibdk_holdingstatus_get_favorites($id);
  }
}


/**
 * Implements hook_field_formatter_info().
 */
function bibdk_holdingstatus_field_formatter_info() {
  return array(
    'bibdk_holdingstatus_favourite_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_holdingstatus_favourite',
      ),
    )
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function bibdk_holdingstatus_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  foreach ($items as $delta => $item) {
    if ($item['favourite']){
      $favourites['link_text'] = t('home_at_favourites');
      $favourites['path'] = 'favourites';
      foreach($item['favourite'] as $key => $favourite){
        $lookupUrl = $favourite['information']->getLookupUrl();
        $localIdentifier = $favourite['holding']['localIdentifier'];
        $item_list[] = theme('favourite_holdings', array(
          'library_name' =>$favourite['information']->getAgencyName(),
          'lid' => $key,
          'pid' => $entity->id,
          'link' =>  ( strpos($lookupUrl, '_IDNR_') !== false ) ? str_replace('_IDNR_', $localIdentifier, $lookupUrl) : $lookupUrl . $localIdentifier,
        ));
      }
      $favourites['favourites'] = array(
        '#theme' => 'item_list',
        '#items' => $item_list,
        '#attributes' => array(
          'class' => array('favourite-list', 'form-item'),
        ),
        '#attached' => array(
          'js' => array(drupal_get_path('module', 'bibdk_holdingstatus') . '/js/bibdk_holdingstatus.js'),
        ),
      );
    $element[$delta]['#markup'] = theme('bibdk_holdings_manifestation_field', $favourites);
    }
  }
  return $element;
}

