<?php

/**
 * @file
 * CTools access plugin to provide access control based
 * upon node editors.
 */

$plugin = array(
  'title' => t("User: Node editors"),
  'description' => t('Control access based upon node editors.'),
  'required context' => array(
    new ctools_context_required(t('User'), 'user'),
    new ctools_context_required(t('Node'), 'node')
  ),
  'callback' => 'plugin_examples_node_editors_access_check',
  'settings form' => 'plugin_examples_node_editors_access_settings_form',
  'settings form submit' => 'plugin_examples_node_editors_access_settings_form_submit',
  'summary' => 'plugin_examples_node_editors_access_summary',
  'default' => array(
    'previous_editors' => TRUE,
  ),
);

/**
 * Access callback.
 */
function plugin_examples_node_editors_access_check($settings, $context, $plugin) {
  // Check for required contexts.
  if (empty($context[0]->data) || empty($context[1]->data) ||
    $context[0]->type[0] != 'entity:user' || $context[1]->type[0] != 'entity:node') {
    return FALSE;
  }

  $query = db_select('node_revision', 'nr');
  $query->condition('nr.nid', $context[1]->data->nid)
    ->fields('nr', array('uid'))
    ->distinct();

  if ($settings['previous_editors']) {
    $last_editor_uid = db_select('node_revision', 'nr')
      ->condition('nr.vid', $context[1]->data->vid)
      ->fields('nr', array('uid'))
      ->execute()
      ->fetchCol();

    $query->condition('nr.uid', $last_editor_uid, '<>');
  }

  $editors = $query->execute()
    ->fetchCol();

  return in_array($context[0]->data->uid, $editors);
}

/**
 * Settings form callback.
 */
function plugin_examples_node_editors_access_settings_form($form, &$form_state, $settings) {
  $form['previous_editors'] = array(
    '#type' => 'checkbox',
    '#title' => t('Previous editors'),
    '#default_value' => $settings['previous_editors'],
    '#description' => t('If checked, only previous node editors (excluding the last one) can access.'),
  );

  return $form;
}

/**
 * Submit callback for settings form.
 */
function plugin_examples_node_editors_access_settings_form_submit($form, &$form_state) {
  $form_state['values']['settings']['previous_editors'] = $form_state['values']['previous_editors'];
}

/**
 * Provide a summary description.
 */
function plugin_examples_node_editors_access_summary($conf, $context) {
  return t('Returns TRUE if user is one of the node editors.');
}
