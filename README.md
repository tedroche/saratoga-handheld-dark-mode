# Enabling dark mode support on handheld.css

This is a set of routines to add support for system- or user-selected light and dark modes to the handheld.css stylesheet used in the Alt-Dashboard scripts for the Saratoga weather website found on https://saratoga-weather.org/scripts-legacy.php#scott, originally developed by Scott of BurnsvilleWeather/WebsterWeather, now retired.

There are three small scripts that let your stylesheets respond to light & dark mode. Here's the code and the flow of operation: when the page loads, darkmode-cell-top.php checks if a preference has been saved and uses that. darkmode-cell-top-setstyle.php adds the appropriate stylesheet HTML code to the top of the page. darkmode-cell-footer.php presents a form (I put it in the bottom footer, it should be movable) to force light or dark mode regardless of the system settings, or to follow whatever the system is set for. It assumes you are using handheld.css, if not, you change it in one place in cell\_top.php, and have created a handheld-dark.css file, as explained in [https://www.wxforum.net/index.php?topic=49715.msg499292\#msg499292](https://www.wxforum.net/index.php?topic=49715.msg499292#msg499292) 

## Darkmode-Cell-top.php

At the top of the cell-top.php script, just before the line that calls Settings.php, add the first line like this:

**require\_once("darkmode-cell-top.inc"); // reads & sets darkmode cookie if selected**  
**require\_once("Settings.php");**

This script sets the CSSDarkMode of the $SITE array to System, Light or Dark, if this script is running after the user makes that selection (in darkmode-cell-footer.php, below). It preserves that setting in a cookie. If there was no form option clicked, it checks for a previous cookie setting and uses that. If there is no cookie, either, like a first-time user, it defaults to the System setting.

`<?php`  
  `// Check to see if darkmode has been selected on a form that calls this page`  
  `if (!empty($_GET['darkmodeswitch']) && in_array($_GET['darkmodeswitch'], array('Disabled','Light','Dark','System'))) {`  
    `$CSSDarkMode = $_GET['darkmodeswitch'] ;`  
    `$SITE['CSSDarkMode'] =  $CSSDarkMode ;`

    `// Preserve this setting in a cookie, checked below if there wasn't an overriding form choice`  
    `$name = "CSSDarkMode";`  
    `$value = $CSSDarkMode;`  
    `$expire = time()+60*60*24*30;`  
    `$path = '/';`  
    `$domain = $_SERVER["HTTP_HOST"] ; // 'contoocook.org' or 'm.contoocook.org';`  
    `$secure = !empty($_SERVER['HTTPS']) ;`  
    `$options = array(`  
      `"expires_or_options" => $expire,`  
      `"path" => $path,`  
      `"domain" => $domain,`  
      `"secure" =>  $secure,`  
      `"httponly" => false,`  
      `"samesite" => 'Lax'`  
    `);`    
    `if(PHP_VERSION_ID < 70300) {`  
       `$result = setcookie("$name",$value,$expire,$path.'; SameSite=Lax');`  
    `} else {`  
      `$result = setcookie($name, $value, $options);`  
    `}`     
    `if ($result == FALSE) error_log("Cookie set failed.");`  
          
    `} else { // if we're not getting passed a choice from the form, check if there is already a cookie`  
    `// use the cookie setting, if set, or default to the System dark mode`

    `if (!empty($_COOKIE['CSSDarkMode'])) { // use User-selected mode Dark or Light`  
       `$SITE['CSSDarkMode'] = $_COOKIE['CSSDarkMode'];`  
      `} else { // or default to system`  
      `$SITE['CSSDarkMode'] = 'System' ;`  
      `}`     
  `}`

## Darkmode-cell-top-setstyle.php

In the cell-top screen, REPLACE the line:   
**`<link rel="stylesheet" type="text/css" href="handheld.css" />`**  
with:  
**`<?php $SITE['CSSscreen'] = "handheld.css"; ?>`**  
**`<link rel="stylesheet" type="text/css" href="<?php echo $SITE['CSSscreen'];?>" />`**  
**`<?php  include('./darkmode-cell-top-setstyle.inc'); ?>`**

This code sets the CSSscreenDark variable to the stylesheet name with \-dark appended. If no such file exists, the CSSDark mode is set to Disabled. But if it does exist, the stylesheet is added to the HTML issues from cell-top.php, based on these rules:  
If CSSDarkMode is set to “Light,” omit the dark stylesheet  
If CSSDarkMode is set to “Dark,” add the stylesheet, which overrides the colors in the primary stylesheet.  
If CSSDarkMode is set to “System,” add the stylesheet with the media query that says it should be used only if the system is set to dark mode.  
If the CSSDarkMode is set to “Disabled,” because the \-dark stylesheet can’t be found, no HTML is added to the form.

`<?php`                                                                                                                                                                                                                
  `$CSSscreenDark = str_replace('.css', '-dark.css', $SITE['CSSscreen']);`                                                                                                                                             
  `$SITE['CSSscreenDark'] = (file_exists($CSSscreenDark)) ? $CSSscreenDark : '' ;`                                                                                                                                     
  `if (empty($SITE['CSSscreenDark'])) { $SITE['CSSDarkMode'] = 'Disabled' ; }`                                                                                                                                         
                                                                                                                                                                                                                     
  `if (!empty($SITE['CSSDarkMode']) && $SITE['CSSDarkMode'] != 'Disabled' ) {`                                                                                                                                         
    `if ($SITE['CSSDarkMode'] == "Dark") { // force dark mode ?>`                                                                                                                                                      
`<link rel="stylesheet" type="text/css" href="<?php echo $SITE['CSSscreenDark']; ?>" />`                                                                                                                               
    `<?php } elseif ($SITE['CSSDarkMode'] == "System") { // load the CSS, but use only if the system is in dark mode ?>`                                                                                               
`<link rel="stylesheet" type="text/css" href="<?php echo $SITE['CSSscreenDark']; ?>" media="screen and (prefers-color-scheme:dark)"/>`                                                                                 
    `<?php }`                                                                                                                                                                                                          
`} // end which stylesheet to invoke`   

## Darkmode-cell-footer.php

Finally, in the cell-footer.php, add a call to darkmode-cell-footer just after the first “\<div\>” tag.

 **`<div id="footer">`**  
   **`<?php require_once("darkmode-cell-footer.inc"); ?>`**

 This presents a small form to the user to pick Light, Dark or System settings. The form shows three radio buttons with the current mode selected and disabled (there’s no point in re-clicking the same button). Each button auto-submits on click, so that will set the $\_GET variable caught in the darkmode-cell-top.php script above.

`<?php if (!empty($SITE['CSSDarkMode']) && $SITE['CSSDarkMode'] != "Disabled") { // Use only if a -dark.css is found ?>`  
`<div>`  
`<form id="darkmodeform" name="darkmodeform" method="get" action="" >`  
  `<fieldset>`  
    `<legend>Screen mode:</legend>`  
    `<!-- <p> <span class="flagwhite">&#9873;</span><span class="flaggreen">&#9873;</span><span class="flagyellow">&#9873;</span><span class="flagred">&#9873;</span><span class="flagblack">&#9873;</span> </p> -->`  
    `<?php $checked = ($SITE['CSSDarkMode'] == 'Light') ? ' checked disabled ' : '' ; ?>`  
    `<label for="light">`  
      `<input type="radio" id="light" name="darkmodeswitch" value="Light" <?php echo "$checked "; ?> onchange="this.form.submit()"/>Light`  
    `</label>`  
    `<?php $checked = ($SITE['CSSDarkMode'] == 'Dark') ? ' checked disabled ' : '' ; ?>`  
    `<label for="dark">`  
      `<input type="radio" id="dark" name="darkmodeswitch" value="Dark" <?php echo "$checked "; ?> onchange="this.form.submit()" />Dark`  
    `</label>`  
    `<?php $checked = ($SITE['CSSDarkMode'] == 'System') ? ' checked disabled ' : '' ; ?>`  
    `<label for="system">`  
      `<input type="radio" id="system" name="darkmodeswitch" value="System" <?php echo "$checked "; ?> onchange="this.form.submit()" />System`  
    `</label>`  
  `</fieldset>`  
`</form>`  
`</div>`  
`<?php } // endif display only if -dark.css is found ?>`

## Optional, advanced features

Creating the handheld-dark.css file for your setup, and adding the three blocks of code above, is sufficient to get dark mode responsiveness on your system. Also attached is a sample handheld-dark.css file I am using on my own site, and some notes on additional changes I made to make the system work better for me. Here’s an excerpt of the handheld-dark.css file:

`/* Dark mode -- handle dark mode completely in this file */`  
`/* add a call to this stylesheet AFTER the regular (light) one */`

`/* manual mode -- uncomment the next line if you don't add all the switcher logic in -footer, Settings and -top */`  
`/* @media (prefers-color-scheme:dark) { /* If the dark scheme is specifically requested: */`

  `:root {`  
    `color-scheme: dark;`  
    `--main-bg-color: black;`  
    `--alt-bg-color:  dimgray;`  
    `--main-fg-color: lightgray;`  
    `--main-anchor-color: lightblue;`  
    `--hover-anchor-color: lightyellow;`  
    `--visited-anchor-color: fuchsia;`  
    `--arrowup-color: lime;`  
    `--arrowdown-color: red;`  
    `--border-color: silver;`  
  `}`  
  `body{`  
    `background-color: var(--main-bg-color) ;`  
    `color: var(--main-fg-color);`  
  `}`

  `a {color: var(--main-anchor-color) ; }`   
  `a:visited {color:var(--visited-anchor-color) ; }`   
  `a:hover {color:var(--hover-anchor-color); }`  
  `.toplinkscell a { color: var(--main-anchor-color) ; }`   
  `.toplinkscell a:visited { color: var(--visited-anchor-color) ; }`   
  `.toplinkscell a:hover { color: var(--hover-anchor-color) ; }` 

  `a.alertlink { color: var(--main-anchor-color) ; }`   
  `a.alertlink:visited { color: var(--visited-anchor-color) ; }`   
  `a.alertlink:hover { color: var(--hover-anchor-color) ; }` 

  `h1{ color: var(--main-fg-color) ; }`   
    
  `h3 { color: var(--main-fg-color) ; }` 

  `/*darkmodeform form switching */`  
  `#darkmodeform input#dark:checked ,`  
  `#darkmodeform input#system:checked {`  
    `cursor: not-allowed;`  
    `opacity: 75%;`  
  `}`  
  `/* hack to insert a light background behind transparent thermometer and compass*/`  
  `td#thermometercontainer {`  
    `background-color: gray;`  
    `background-image: linear-gradient(147deg, lightgray 0%, gray 100%) ;`  
    `border-radius: 20px;`  
  `}`

  `/* metal effect cite: cite: https://www.eggradients.com/gradient/moon-spot*/`  
  `td#windicbox {`  
    `background-color: #f5f5f5;`  
    `background-image: linear-gradient(147deg, #f5f5f5 0%, #8c92ac 100%);`  
    `border-radius: 37px;`  
    `width: 74px;`  
  `}`  
  `/* end of hack */`

Key points to consider in converting pages to being dark-mode compliant:`

1. You want all changes to colors in the CSS files, and out of the running code. This lets you support new modes and color templates without changing code. Especially for this light/dark process, the PHP code that runs the site is not aware of whether the system is set to light or dark, and the CSS automatically switches, without running any of the PHP code that runs the site.  
2. If you need to modify an existing page, the ideal solution is to “tag” the element that needs color-changing with an id=”uniquename” or class=”specificClassOfElements” and make those changes in the handheld.css and handheld-dark.css pages. This minimizes the place you have to look for color settings
     
   In some cases, like the Steel Series gauges that come with their own css page, you might want to modify the code shown here to support a separate -dark.css like the code in darkmode-cell-top-setstyle.php, as there is a lot of CSS code and it is unlikely to be reused outside of this single page. Having a separate -dark.css also has the advanage that you can drop in updates to the supplied CSS without overwriting your -dark.css file.  
3. Many, many elements have their colors hard-coded into their web pages, either with their own CSS files, inline <style>...</style> declarations, or with inline style="" declarations.
4. The handheld.css is the primary file, containing the colors of light mode, as well as the structure, font and any other CSS characteristics. The -dark file is a supplmental file that overrides only the color settings of the primary file. This elminiates unnecessary duplication making maintenance easier.

