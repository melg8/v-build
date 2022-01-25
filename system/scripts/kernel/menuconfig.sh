#!/bin/bash

if [ $# -ne 1 ]; then
	printf "invalid argument count. exit.\n"
	exit 1
fi

linux_dir=$1

if [ ! -d "${linux_dir}" ]; then
	printf "directory "${linux_dir}" not found, exit.\n"
	exit 1
fi

cd ${linux_dir} && make MENUCONFIG_COLOR=blackbg menuconfig

exit 0



