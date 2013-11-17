<?php

/**
 * @file
 * Built in Goto operation plugin for One click.
 */

$plugin = array(
  'title' => t('Goto'),
  'execute' => 'one_click_goto_operation_execute',
  'validate input' => 'one_click_goto_operation_validate_input',
);

/**
 * Execute callback.
 */
function one_click_goto_operation_execute($value) {
  drupal_goto($value);
}

/**
 * Validate input callback.
 */
function one_click_goto_operation_validate_input($value) {
  if (!drupal_valid_path($value)) {
    return array('The path "' . $value . '" is not a valid path');
  }
}
