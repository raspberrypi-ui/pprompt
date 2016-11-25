#!/bin/bash

SALT=$(sudo grep pi /etc/shadow | sed -n 's/pi:\$6\$//;s/\$.*//p')
HASH=$(mkpasswd -msha-512 raspberry "$SALT")

if service ssh status | grep -q running && sudo grep -q "$HASH" /etc/shadow ; then
	zenity --warning --text="SSH is enabled and the default password for the 'pi' user has not been changed.\nThis is a security risk - please login as the 'pi' user and run Raspberry Pi Configuration to set a new password."
fi
