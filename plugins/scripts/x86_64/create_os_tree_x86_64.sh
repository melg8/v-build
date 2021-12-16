#!/bin/bash

# Create sdz os tree X86_64

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
COUNTER=1

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "${NC}$1 ${GREEN}$2${NC}\n" ; }
function msg_red(){ printf "${NC}$1 ${RED}$2${NC}\n" ; }

if [ -d "${V_BUILD_TREE_X86_64}" ]; then
	msg_red "" "\tV BUILD Tree already exist"
	exit 1
fi

mkdir ${V_BUILD_TREE_X86_64}

pushd ${V_BUILD_TREE_X86_64} > /dev/null 2>&1

mkdir -p tools lib64 etc var usr/{bin,lib,sbin}

ln -s usr/bin bin
ln -s usr/lib lib
ln -s usr/sbin sbin

msg_green "Arch: $1" "Tree created"

popd > /dev/null 2>&1

exit 0
