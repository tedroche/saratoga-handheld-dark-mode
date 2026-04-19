<?php
############################################################################
#   Project:    darkmode support for handheld.css sites
#   Module:     darkmode-cell-footer.inc; see darkmode-cell-top.inc for details & license
#   Purpose:    Presents a radiobutton form to switch modes
############################################################################
?>
<?php if (!empty($SITE['CSSDarkMode']) && $SITE['CSSDarkMode'] != "Disabled") { // Use only if a -dark.css is found ?>
<div>
<form id="darkmodeform" name="darkmodeform" style="width:18em;margin:auto;" method="get" action="" >
  <fieldset>
    <legend>Screen mode:</legend>
    <?php $checked = ($SITE['CSSDarkMode'] == 'Light') ? ' checked disabled ' : '' ; ?>
    <label for="light">
      <input type="radio" id="light" name="darkmodeswitch" value="Light" <?php echo "$checked "; ?> onchange="this.form.submit()"/>Light
    </label>
    <?php $checked = ($SITE['CSSDarkMode'] == 'Dark') ? ' checked disabled ' : '' ; ?>
    <label for="dark">
      <input type="radio" id="dark" name="darkmodeswitch" value="Dark" <?php echo "$checked "; ?> onchange="this.form.submit()" />Dark
    </label>
    <?php $checked = ($SITE['CSSDarkMode'] == 'System') ? ' checked disabled ' : '' ; ?>
    <label for="system">
      <input type="radio" id="system" name="darkmodeswitch" value="System" <?php echo "$checked "; ?> onchange="this.form.submit()" />System
    </label>
  </fieldset>
</form>
</div>
<?php } // endif display only if -dark.css is found ?>
