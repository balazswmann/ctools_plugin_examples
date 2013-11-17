<?php

/**
 * @file
 * Panels style plugin to display the region's content
 * as collapsible.
 */

$plugin = array(
  'title' => t('Collapsible'),
  'description' => t('Displays region content as collapsible'),
  'render region' => 'plugin_examples_collapsible_style_render_region',
  'settings form' => 'plugin_examples_collapsible_style_settings_form',
  'settings form submit' => 'plugin_examples_collapsible_style_settings_form_submit',
  'defaults' => array(
    'title' => t('Content'),
    'collapsed' => TRUE,
  ),
);

/**
 * Region render callback.
 */
function theme_plugin_examples_collapsible_style_render_region($vars) {
  $panes = array();
  foreach ($vars['panes'] as $pane) {
    $panes[] = array('#markup' => $pane);
  }

  // Using form API without any form.
  $region = array(
    '#type' => 'fieldset',
    '#title' => $vars['settings']['title'],
    '#attributes' => array('class' => array('collapsible')),
    'panes' => $panes,
    '#attached' => array(
      'js' => array('misc/form.js', 'misc/collapse.js'),
    ),
  );

  if ($vars['settings']['collapsed']) {
    $region['#attributes']['class'][] = 'collapsed';
  }

  return drupal_render($region);
}

/**
 * Settings form callback.
 */
function plugin_examples_collapsible_style_settings_form($settings, $display, $pid, $type, $form_state) {
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $settings['title'],
    '#description' => t('The title of the fieldset.'),
    '#required' => TRUE,
  );
  $form['collapsed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Collapsed'),
    '#default_value' => $settings['collapsed'],
    '#description' => t('If checked, contents appear collapsed.'),
  );

  return $form;
}

/**
 * Submit callback for settings form.
 */
function plugin_examples_collapsible_style_settings_form_submit($form, $settings, &$form_state) {
  $form_state['conf']['title'] = $settings['title'];
  $form_state['conf']['collapsed'] = $settings['collapsed'];
}
