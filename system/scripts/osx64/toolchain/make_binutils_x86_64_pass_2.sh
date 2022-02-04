#!/bin/bash

# Create toolchain, PASS 2
# linker, assembler, compiler
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

# determind arch type
ARCH=$V_BUILD_TGT_X86_64

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

# build binutils - PASS 2
function install_binutils_pass_2(){
	msg_green "Pkg found:" $BINUTILS

	rm -rf $V_BUILD_PKG_DIR/$BINUTILS/$BINUTILS/build
	mkdir -p $V_BUILD_PKG_DIR/$BINUTILS/$BINUTILS/build

	msg_green "" "PASS - 2"

	pushd $V_BUILD_PKG_DIR/$BINUTILS/$BINUTILS/build
	sh ../configure \
	--prefix=/usr \
	--build=$(../config.guess) \
	--host=$ARCH \
	--disable-nls \
	--enable-shared \
	--disable-werror \
	--enable-64-bit-bfd

	press_any_key

	make -j`nproc`
	make DESTDIR=${V_BUILD_TREE_X86_64} install -j1

	# workaround of error libctf
	install -vm755 libctf/.libs/libctf.so.0.0.0 ${V_BUILD_TREE_X86_64}/usr/lib

	popd
}

################################## Main ########################################

if [ ! -d "${V_BUILD_DIR}" ]; then
	printf "env variables don't set, exit.\n"
	exit 1
fi

if [ ! -d "${V_BUILD_TOOLS_X86_64}" ]; then
	printf "env variables don't set, exit.\n"
	exit 1
fi

msg_green "Making binutils" "PASS 2"

BINUTILS=$(find_package "binutils")

msg "$BINUTILS"

install_binutils_pass_2

msg_green "Binutils-pass 2 has been" "built."

exit 0

