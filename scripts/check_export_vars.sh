#!/bin/bash

# check sdz os variables existance

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
COUNTER=1

BINUTILS="none"
GCC="none"

function msg_green(){ printf "${NC}$1 ${GREEN}$2${NC}\n" ; }

declare -a vars=(
"1"
"V_BUILD_DIR"
"V_BUILD_PKG_DIR"
"V_BUILD_PRIVATE"
"V_BUILD_BUILD_DIR"
"V_BUILD_PATCH_DIR"
"V_BUILD_ARCHIVE_DIR"
"2"
"V_BUILD_TGT_X86_64"
"V_BUILD_TREE_X86_64"
"V_BUILD_TOOLS_X86_64"
"V_BUILD_PRIVATE_X86_64"
"3"
"LINUX_KERNEL")

for i in "${vars[@]}"
do
	# get value of value
	msg_green "$i: " "${!i}"
done

msg_green "Check variables" "complete\n"

sleep 0.5
exit 0

