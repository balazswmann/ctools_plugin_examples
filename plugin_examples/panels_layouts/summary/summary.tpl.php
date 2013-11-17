<?php

/**
 * @file
 * Template for Summary layout.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['summary']: Summary in the top row
 *   - $content['body']: Body on the left side under the summary
 *   - $content['sidebar']: Sidebar on the right side under the summary
 */

?>

<div class="panel-display panel-summary clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <div class="region summary">
    <div class="inside">
      <?php print $content['summary']; ?>
    </div>
  </div>
  <div class="content-wrapper">
    <div class="region content">
      <div class="inside">
        <?php print $content['content']; ?>
      </div>
    </div>
    <div class="region right-sidebar">
      <div class="inside">
        <?php print $content['right_sidebar']; ?>
      </div>
    </div>
    <div class="clearer"></div>
  </div>
</div>
