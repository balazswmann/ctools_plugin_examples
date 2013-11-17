<?php

/**
 * @file
 * Panels layout plugin to provide Summary layout.
 */

$plugin = array(
  'title' => t('Summary'),
  'category' => t('Custom'),
  'icon' => 'summary.png',
  'css' => 'summary.css',
  'theme' => 'summary',
  'regions' => array(
    'summary' => t('Summary'),
    'content' => t('Content'),
    'right_sidebar' => t('Right sidebar'),
  ),
);
