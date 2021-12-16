#!/bin/bash

# install C++ library

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "\n${NC}$1 ${GREEN}$2${NC}\n\n" ; }
function msg_red(){ printf "\n${NC}$1 ${RED}$2${NC}\n\n" ; }

LIBSTDCPP="none"
GCC="none"
ARCH=$V_BUILD_TGT_X86_64

############################# Functions ########################################

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

# find gcc lib
function find_libstdcpp(){
	local search_pkg=$1
	local res=$(ls ${V_BUILD_PKG_DIR}/${GCC}/${GCC} | grep $search_pkg)

	if [ -z "$res" ]; then
		msg_red "Pkg not found:" "$search_pkg"
		exit 1
	else
		echo $res
	fi
}


function install_libstdcpp(){	
	msg_green "Package found: " "$LIBSTDCPP"

	if [ -d ${V_BUILD_BUILD_DIR}/${LIBSTDCPP} ]; then
		pushd ${V_BUILD_BUILD_DIR}/${LIBSTDCPP} > /dev/null 2>&1
		make uninstall
		popd > /dev/null 2>&1
	fi

	rm -rf ${V_BUILD_BUILD_DIR}/${LIBSTDCPP}
	mkdir ${V_BUILD_BUILD_DIR}/${LIBSTDCPP}

	pushd ${V_BUILD_BUILD_DIR}/${LIBSTDCPP} > /dev/null 2>&1

	sh ${V_BUILD_PKG_DIR}/$GCC/$GCC/$LIBSTDCPP/configure \
	--host=$V_BUILD_TGT_X86_64 \
	--build=$(${V_BUILD_PKG_DIR}/$GCC/$GCC/config.guess) \
	--prefix=/usr \
	--disable-multilib \
	--disable-nls \
	--disable-libstdcxx-pch \
	--with-gxx-include-dir=/tools/$V_BUILD_TGT_X86_64/include/c++/10.3.0

	make
	make DESTDIR=$V_BUILD_TREE_X86_64 install

	popd > /dev/null 2>&1
}

#################################### Main ######################################

GCC=$(find_package "gcc")
LIBSTDCPP=$(find_libstdcpp "libstdc++")

install_libstdcpp

msg_green "" "$LIBSTDCPP has been built."

exit 0

