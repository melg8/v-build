#!/bin/bash

if [ $# -ne 2 ]; then
	printf "invalid argument count. exit.\n"
	exit 1
fi

linux_dir=$1
config=$2

base="scripts/kernel/configs"
path=""

function copy_config(){
	if [ ! -d "${linux_dir}" ]; then
		printf "linux directory not found. exit.\n"
		exit 1
	else
		if [ ! -f "${linux_dir}/.config" ]; then
			printf "config file in ${linux_dir} not found, exit.\n"
			exit 1
		fi

		cp "${linux_dir}/.config" "${path}"
		printf "done\n"
	fi
}

if [ -d "../system" ]; then
	path="../system/${base}/${config}"
else
	printf "directory \"system\" not found, exit\n"
	exit 1
fi

copy_config


exit 0



