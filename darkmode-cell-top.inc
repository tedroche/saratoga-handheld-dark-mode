<?php

############################################################################
#
#   Project:    darkmode support for handheld.css sites
#   Module:     darkmode-cell-top.inc
#   Purpose:    Set $SITE['CSSDarkMode'] from user, cookie or default
#   Author:     Ted Roche <contoocook.org> inspired by
#   Based on:   Kevin W. Reed <kreed@tnet.com> TNET Services, Inc.
#               Ken True, <saratoga-weather.org>
#                ... and the many who came before
#   Files: darkmode-cell-top.inc, darkmode-cell-top-setstyle.inc 
#          darkmode-cell-footer.inc, handheld-dark.css
#   Copyright:  (c) 1992-2007 Copyright TNET Services, Inc.
############################################################################
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA
############################################################################
# This document uses double spaces
############################################################################
// Version 0.89 beta - 19-Apr-2026 - first public release
############################################################################
# No user-modifiable settings
############################################################################
  // Check to see if darkmode has been selected on a form that calls this page
  if (!empty($_GET['darkmodeswitch']) && in_array($_GET['darkmodeswitch'], array('Disabled','Light','Dark','System'))) {
    $CSSDarkMode = $_GET['darkmodeswitch'] ;
    $SITE['CSSDarkMode'] =  $CSSDarkMode ;

    // Preserve this setting in a cookie, checked below if there wasn't an overriding form choice
    $name = "CSSDarkMode";
    $value = $CSSDarkMode;
    $expire = time()+60*60*24*30;
    $path = '/';
    $domain = $_SERVER["HTTP_HOST"] ;
    $secure = !empty($_SERVER['HTTPS']) ;
    $options = array(
      "expires_or_options" => $expire,
      "path" => $path,
      "domain" => $domain,
      "secure" =>  $secure,
      "httponly" => false,
      "samesite" => 'Lax'
    );
    if(PHP_VERSION_ID < 70300) {
       $result = setcookie("$name",$value,$expire,$path.'; SameSite=Lax');
    } else {
      $result = setcookie($name, $value, $options);
    }
    if ($result == FALSE) error_log("Cookie set failed.");

    } else { // if we're not getting passed a choice from the form, check if there is already a cookie
    // use the cookie setting, if set, or default to the System dark mode

    if (!empty($_COOKIE['CSSDarkMode'])) { // use User-selected mode Dark or Light
       $SITE['CSSDarkMode'] = $_COOKIE['CSSDarkMode'];
      } else { // or default to system
      $SITE['CSSDarkMode'] = 'System' ;
      }
  }
