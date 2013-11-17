<?php

/**
 * @file
 * CTools content type plugin to display the name of
 * the user the referenced node was last updated by.
 */

$plugin = array(
  'single' => TRUE,
  'category' => array(t('Node'), -9),
  'title' => t('Node last updated by'),
  'description' => t('The name of the user the referenced node was last updated by.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'render callback' => 'plugin_examples_last_updated_by_content_type_render',
  'edit form' => 'plugin_examples_last_updated_by_content_type_settings_form',
  'icon' => drupal_get_path('module', 'ctools') . '/plugins/content_types/node_context/icon_node.png',
  'admin title' => 'plugin_examples_last_updated_by_content_type_admin_title',
  'hook theme' => 'plugin_examples_last_updated_by_content_type_hook_theme',
  'defaults' => array(
    'link_to_profile' => TRUE,
  ),
);

/**
 * Render callback.
 */
function plugin_examples_last_updated_by_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass;

  $block->title = $conf['override_title'] ? $conf['override_title_text'] : 'Last updated by';

  if (empty($context->data) || $context->keyword != 'node') {
    return $block;
  }

  $last_updated = db_select('node_revision', 'nr');
  $last_updated->condition('nr.nid', $context->data->nid);
  $last_updated->addExpression('MAX(nr.timestamp)', 'timestamp');

  $query = db_select('node_revision', 'nr');
  $query->join($last_updated, 'last_updated', 'nr.timestamp = last_updated.timestamp');
  $query->condition('nr.nid', $context->data->nid)
    ->fields('nr', array('uid'));

  $uid = $query->execute()
    ->fetchField();

  $block->content = array(
    '#uid' => $uid,
    '#link_to_profile' => $conf['link_to_profile'],
    '#theme' => 'plugin_examples_last_updated_by_content_type_username',
  );
  return $block;
}

/**
 * Settings form callback.
 */
function plugin_examples_last_updated_by_content_type_settings_form($form, &$form_state) {
  $form['link_to_profile'] = array(
    '#type' => 'checkbox',
    '#title' => t('Link to user profile'),
    '#default_value' => $form_state['conf']['link_to_profile'],
    '#description' => t('If checked, user name will be linked to the user profile.'),
  );

  return $form;
}

/**
 * Submit callback for settings form.
 */
function plugin_examples_last_updated_by_content_type_settings_form_submit($form, &$form_state) {
  $form_state['conf']['link_to_profile'] = $form_state['values']['link_to_profile'];
}

/**
 * Returns the administrative title for the content type.
 */
function plugin_examples_last_updated_by_content_type_admin_title($subtype, $conf, $context) {
  return t('"@context_id" last updated by', array('@context_id' => $context->identifier));
}

/**
 * Callback to provide plugin specific theme functions.
 */
function plugin_examples_last_updated_by_content_type_hook_theme(&$theme, $plugin) {
  $theme['plugin_examples_last_updated_by_content_type_username'] = array(
    'path' => $plugin['path'],
    'file' => 'last_updated_by.inc',
    'function' => 'plugin_examples_last_updated_by_content_type_theme_username',
    'variables' => array(
      'uid' => NULL,
      'link_to_profile' => TRUE,
    ),
  );
}

/**
 * Theme function to render a username.
 */
function plugin_examples_last_updated_by_content_type_theme_username($variables) {
  if ($variables['uid'] == NULL) {
    return NULL;
  }

  $account = user_load($variables['uid']);

  if ($variables['link_to_profile']) {
    return l($account->name, 'user/' . $account->uid, array(
      'attributes' => array(
        'title' => t('View user profile.'),
      ),
    ));
  }

  return $account->name;
}
