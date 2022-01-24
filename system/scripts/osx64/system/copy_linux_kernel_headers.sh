#!/bin/bash

# copy kernel project headers into tree

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "\n${NC}$1 ${GREEN}$2${NC}\n\n" ; }
function msg_red(){ printf "\n${NC}$1 ${RED}$2${NC}\n\n" ; }

V_BUILD_KERNEL_X86_64=$1

if [ -z ${V_BUILD_KERNEL_X86_64} ]; then
	msg_red "Error, path not found:" "\$V_BUILD_KERNEL_X86_64"
	msg "Run: make help\n"
	exit 1
fi


if [ ! -d "${V_BUILD_TREE_X86_64}" ]; then
	msg_red "\$V_BUILD_TREE" "do not exist!"
	exit 1
fi

msg_green "Copy headers from: " "$V_BUILD_KERNEL_X86_64"

cd $V_BUILD_KERNEL_X86_64 && make distclean
cd $V_BUILD_KERNEL_X86_64 && make INSTALL_HDR_PATH="${V_BUILD_TREE_X86_64}/usr" headers_install 

msg_green "kernel headers were copied into: " "$V_BUILD_TREE_X86_64/usr/include"

exit 0


