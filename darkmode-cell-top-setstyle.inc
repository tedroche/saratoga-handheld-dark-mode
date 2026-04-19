<?php
############################################################################
#   Project:    darkmode support for handheld.css sites
#   Module:     darkmode-cell-top-setstyle.inc; see darkmode-cell-top.inc for details & license
#   Purpose:    sets the dark-mode stylesheet if appropriate
############################################################################
  $CSSscreenDark = str_replace('.css', '-dark.css', $SITE['CSSscreen']);
  $SITE['CSSscreenDark'] = (file_exists($CSSscreenDark)) ? $CSSscreenDark : '' ;
  if (empty($SITE['CSSscreenDark'])) { $SITE['CSSDarkMode'] = 'Disabled' ; }

  if (!empty($SITE['CSSDarkMode']) && $SITE['CSSDarkMode'] != 'Disabled' ) {
    if ($SITE['CSSDarkMode'] == "Dark") { // force dark mode ?>
<link rel="stylesheet" type="text/css" href="<?php echo $SITE['CSSscreenDark']; ?>" />
    <?php } elseif ($SITE['CSSDarkMode'] == "System") { // load the CSS, but use only if the system is in dark mode ?>
<link rel="stylesheet" type="text/css" href="<?php echo $SITE['CSSscreenDark']; ?>" media="screen and (prefers-color-scheme:dark)"/>
    <?php } // end which stylesheet to invoke 
} // end if darkmode is not disabled 
