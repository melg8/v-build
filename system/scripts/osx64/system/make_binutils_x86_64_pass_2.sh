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

	rm -rf $V_BUILD_BUILD_DIR/$BINUTILS
	mkdir -p $V_BUILD_BUILD_DIR/$BINUTILS

	msg_green "" "PASS - 2"

	pushd $V_BUILD_BUILD_DIR/$BINUTILS
	sh $V_BUILD_PKG_DIR/$BINUTILS/$BINUTILS/configure \
	--prefix=/usr \
	--build=$($V_BUILD_PKG_DIR/$BINUTILS/$BINUTILS/config.guess) \
	--host=$ARCH \
	--disable-nls \
	--enable-shared \
	--disable-werror \
	--enable-64-bit-bfd \
	--with-build-libsubdir=${V_BUILD_TREE_X86_64}/usr/lib \
	--libdir=${V_BUILD_TREE_X86_64}/usr/lib \
	LD_FOR_TARGET=${V_BUILD_TREE_X86_64}/tools/x86_64-linux-gnu/bin/ld
	
	make -j`nproc`
	make DESTDIR=${V_BUILD_TREE_X86_64} \
		LDFLAGS=${V_BUILD_TREE_X86_64}/usr/lib \
		install -j1

	# workaround of error libctf
	install -vm755 libctf/.libs/libctf.so.0.0.0 ${V_BUILD_TREE_X86_64}/usr/lib

	popd
}

################################## Main ########################################

msg_green "Making binutils" "PASS 2"

BINUTILS=$(find_package "binutils")

msg "$BINUTILS"

install_binutils_pass_2

msg_green "Binutils-pass 2 has been" "built."

exit 0

