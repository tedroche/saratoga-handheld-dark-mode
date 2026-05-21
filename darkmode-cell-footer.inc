<?php
############################################################################
#   Project:    darkmode support for handheld.css sites
#   Module:     darkmode-cell-footer.inc; see darkmode-cell-top.inc for details & license
#   Purpose:    Presents a radiobutton form to switch modes
############################################################################
?>
<?php if (!empty($SITE['CSSDarkMode']) && $SITE['CSSDarkMode'] != "Disabled") { // Use only if a -dark.css is found ?>
<?php $darkmode_params= array();
  if (!empty($_SERVER['QUERY_STRING'])) $result = parse_str($_SERVER['QUERY_STRING'], $darkmode_params) ;
?> 
<div>
<form id="darkmodeform" name="darkmodeform" style="width:18em;margin:auto;" method="get" action="" >
  <?php
  // DEBUG: echo "<!-- darkmodeparams are ".print_r($darkmode_params, TRUE)." --> \n" ;
  foreach ($darkmode_params as $key => $value) {
    if ($key != 'darkmodeswitch') { // skip this one, that's what the form below sets!
      echo "<input type=\"hidden\" name=\"$key\" value=\"$value\" /> \n";
    } // endif the parameter is darkmodeswitch, skip
  } //end-foreach 
  ?> 
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
