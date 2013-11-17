<?php

/**
 * @file
 * One click operation plugin to provide node delete
 * operation.
 */

$plugin = array(
  'title' => t('Node delete'),
  'execute' => 'plugin_examples_node_delete_operation_execute',
  'validate input' => 'plugin_examples_node_delete_operation_validate_input',
  'success message' => 'plugin_examples_node_delete_operation_success_message',
);

/**
 * Execute callback.
 */
function plugin_examples_node_delete_operation_execute($value) {
  node_delete($value);
}

/**
 * Validate input callback.
 */
function plugin_examples_node_delete_operation_validate_input($value) {
  $node = node_load($value);

  if (!$node) {
    return array('The node nid "' . $value . '" doesn\'t exist');
  }
  else {
    $permission_1 = 'delete_own_' . $node->type . '_content';
    $permission_2 = 'delete_any_' . $node->type . '_content';
    if (!user_access($permission_1) && !user_access($permission_2)) {
      return array('You don\'t have permission to delete the node with nid "' . $value . '"');
    }
  }
}

/**
 * Success message callback.
 */
function plugin_examples_node_delete_operation_success_message($value) {
  return 'The node with the nid "' . $value . '" successfully deleted.';
}
