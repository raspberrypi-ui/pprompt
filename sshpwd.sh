#!/bin/bash

check_hash ()
{
   test -x /usr/bin/mkpasswd || return 0
   local SHADOW="$(sudo -n grep -E '^pi:' /etc/shadow 2>/dev/null)"
   test -n "${SHADOW}" || return 0
   if echo $SHADOW | grep -q "pi:!" ; then return 0 ; fi
   local SALT=$(echo "${SHADOW}" | sed -n 's/pi:\$6\$//;s/\$.*//p')
   local HASH=$(mkpasswd -msha-512 raspberry "$SALT")
   test -n "${HASH}" || return 0

   if systemctl is-active ssh -q && echo "${SHADOW}" | grep -q "${HASH}"; then
	zenity --warning --text="SSH is enabled and the default password for the 'pi' user has not been changed.\nThis is a security risk - please login as the 'pi' user and run Raspberry Pi Configuration to set a new password."
   fi
}

check_hash
unset check_hash