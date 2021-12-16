#!/bin/bash

# copy sdz-kernel project headers into tree

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "\n${NC}$1 ${GREEN}$2${NC}\n\n" ; }
function msg_red(){ printf "\n${NC}$1 ${RED}$2${NC}\n\n" ; }

LINUX_KERNEL=$1

if [ -z ${LINUX_KERNEL} ]; then
	msg_red "Error, path not found:" "\$LINUX_KERNEL"
	msg "Run: make help\n"
	exit 1
fi


if [ ! -d "${V_BUILD_TREE_X86_64}" ]; then
	msg_red "\$V_BUILD_TREE" "do not exist!"
	exit 1
fi

msg_green "Copy headers from: " "$LINUX_KERNEL"

cd $LINUX_KERNEL && make distclean
cd $LINUX_KERNEL && make install-hdr HDR_PATH="${V_BUILD_TREE_X86_64}/usr"

msg_green "sdz-kernel headers were copied into: " "$V_BUILD_TREE_X86_64/usr/include"

exit 0


