#!/bin/bash

# check OS variables existance

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
COUNTER=1

function msg_green(){ printf "${NC}$1 ${GREEN}$2${NC}\n" ; }
function msg_red(){ printf "${NC}$1 ${RED}$2${NC}\n" ; }

declare -a vars=(
"PATH"
"V_BUILD_DIR"
"V_BUILD_PKG_DIR"
"V_BUILD_SYSTEM"
"V_BUILD_PATCH_DIR"
"V_BUILD_ARCHIVE_DIR"
"V_BUILD_TGT_ARM64"
"V_BUILD_TREE_ARM64"
"V_BUILD_TOOLS_ARM64"
"V_BUILD_KERNEL_ARM64")

for i in "${vars[@]}"
do
	if [ "${!i}" = "" ]; then
		msg_red "$i: " "no"
	else
		# get value of value
		msg_green "$i: " "${!i}"
	fi
done

exit 0

