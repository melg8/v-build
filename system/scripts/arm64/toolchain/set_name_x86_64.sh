#!/bin/bash

# set `uname -m` inside building directory in file ".machine_name"

if [ -e ".machine_name" ]; then
	printf "file \".machine_name\" already exist, check it\n"
	exit 0
fi

uname -m >> .machine_name

exit 0

