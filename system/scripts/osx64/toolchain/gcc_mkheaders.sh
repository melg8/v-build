#!/bin/bash

# Install gcc headers

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
PKG_COUNTER=1

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "${NC}$1 ${GREEN}$2${NC}" ; }
function msg_red(){ printf "${NC}$1 ${RED}$2${NC}" ; }

# find gcc pkg version in PKG dir
function find_package_gcc_version(){
	local search_pkg=$1
	local res=$(ls ${V_BUILD_PKG_DIR} | grep $search_pkg | sed 's/gcc-//')

	if [ -z "$res" ]; then
		msg_red "Pkg not found:" "$search_pkg"
		exit 1
	else
		echo $res
	fi
}

if [ ! -d "${V_BUILD_DIR}" ]; then
	printf "env variables don't set, exit.\n"
	exit 1
fi

if [ ! -d "${V_BUILD_TOOLS_X86_64}" ]; then
	printf "env variables don't set, exit.\n"
	exit 1
fi

GCC_VER=$(find_package_gcc_version "gcc")

$V_BUILD_TOOLS_X86_64/libexec/gcc/$V_BUILD_TGT_X86_64/$GCC_VER/install-tools/mkheaders | \
	msg_green "\nGCC headers" "installed\n"

exit 0



