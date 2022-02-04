#!/bin/bash

# Create binutils:
# linker, assembler
#
# Arch:
# x86_64

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
COUNTER=1

BINUTILS="none"

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "\n${NC}$1 ${GREEN}$2${NC}\n" ; }
function msg_red(){ printf "\n${NC}$1 ${RED}$2${NC}\n" ; }
function press_any_key() { read -n 1 -s -r -p "Press any key to continue" ; }

################################## Functions ###################################

# find package in PKG dir
function find_package(){
	local search_pkg=$1
	local res=$(ls ${V_BUILD_PKG_DIR} | grep $search_pkg)

	if [ -z "$res" ]; then
		msg_red "Pkg not found:" "$search_pkg"
		exit 1
	else
		echo $res
	fi
}

# build binutils - PASS 1
function install_binutils_pass_1(){
	msg_green "Pkg found:" $BINUTILS

	rm -rfv $V_BUILD_PKG_DIR/$BINUTILS/$BINUTILS/build
	mkdir -pv $V_BUILD_PKG_DIR/$BINUTILS/$BINUTILS/build

	msg_green "" "PASS - 1"
	
	pushd $V_BUILD_PKG_DIR/$BINUTILS/$BINUTILS/build

	sh ../configure \
	--prefix=$V_BUILD_TOOLS_X86_64 \
	--with-sysroot=$V_BUILD_TREE_X86_64 \
	--target=$V_BUILD_TGT_X86_64 \
	--disable-nls \
	--disable-werror

	press_any_key

	make
	make install

	popd
}

################################## Main ########################################

if [ ! -f "${V_BUILD_DIR}/.extracted" ]; then
	msg_red "" "packages are not extracted yet"
	exit 1
elif [ ! -d "${V_BUILD_TREE_X86_64}" ]; then
	msg_red "" "tree do not exist!"
	exit 1
else
	BINUTILS=$(find_package "binutils")

	install_binutils_pass_1

	msg_green "" "Binutils-pass 1 has been built."
fi

exit 0

