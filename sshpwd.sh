#!/bin/bash

SALT=$(sudo grep pi /etc/shadow | sed -n 's/pi:\$6\$//;s/\$.*//p')
HASH=$(mkpasswd -msha-512 raspberry "$SALT")

if service ssh status | grep -q running && sudo grep -q "$HASH" /etc/shadow ; then
	pprompt
fi
