#!/bin/bash

export TEXTDOMAIN=pprompt

. gettext.sh

if [ -e /run/sshwarn ] ; then
	zenity --warning --width=400 --text="$(gettext "SSH is enabled and the default password for the 'pi' user has not been changed.\n\nThis is a security risk - please login as the 'pi' user and run Raspberry Pi Configuration to set a new password.")"
fi
