#!/bin/bash

# check OS variables existance

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
COUNTER=1

function msg_green(){ printf "${NC}$1 ${GREEN}$2${NC}\n" ; }

msg_green "Preparing current directory" "running\n"

printf "V_BUILD_PKG_DIR=%s\n" "$V_BUILD_PKG_DIR"
printf "V_BUILD_BUILD_DIR=%s\n" "$V_BUILD_BUILD_DIR" 
printf "V_BUILD_PATCH_DIR=%s\n" "$V_BUILD_PATCH_DIR"
printf "V_BUILD_ARCHIVE_DIR=%s\n" "$V_BUILD_ARCHIVE_DIR"
printf "V_BUILD_TGT_X86_64=%s\n" "$V_BUILD_TGT_X86_64"
printf "V_BUILD_TREE_X86_64=%s\n" "$V_BUILD_TREE_X86_64"
printf "V_BUILD_TOOLS_X86_64=%s\n" "$V_BUILD_TOOLS_X86_64"
printf "V_BUILD_SYSTEM_X86_64=%s\n" "$V_BUILD_SYSTEM_X86_64"
printf "LINUX_KERNEL=%s\n" "$LINUX_KERNEL"

sleep 0.5
exit 0

