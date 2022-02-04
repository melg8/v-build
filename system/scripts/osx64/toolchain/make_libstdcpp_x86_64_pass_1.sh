#!/bin/bash

# install C++ library

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "\n${NC}$1 ${GREEN}$2${NC}\n\n" ; }
function msg_red(){ printf "\n${NC}$1 ${RED}$2${NC}\n\n" ; }
function press_any_key() { read -n 1 -s -r -p "Press any key to continue" ; }

LIBSTDCPP="none"
GCC="none"
GCC_VER="none"
ARCH=$V_BUILD_TGT_X86_64

############################# Functions ########################################

# find gcc pkg verions in PKG dir
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

	rm -rf ${V_BUILD_PKG_DIR}/$GCC/$GCC/build
	mkdir ${V_BUILD_PKG_DIR}/$GCC/$GCC/build

	pushd ${V_BUILD_PKG_DIR}/$GCC/$GCC/build

	sh ../libstdc++-v3/configure \
	--host=$V_BUILD_TGT_X86_64 \
	--build=$(../config.guess) \
	--prefix=/usr \
	--disable-multilib \
	--disable-nls \
	--disable-libstdcxx-pch \
	--with-gxx-include-dir=/tools/$V_BUILD_TGT_X86_64/include/c++/$GCC_VER

	press_any_key

	make
	make DESTDIR=$V_BUILD_TREE_X86_64 install

	popd > /dev/null 2>&1
}

#################################### Main ######################################

if [ ! -d "${V_BUILD_DIR}" ]; then
	printf "env variables don't set, exit.\n"
	exit 1
fi

if [ ! -d "${V_BUILD_TOOLS_X86_64}" ]; then
	printf "env variables don't set, exit.\n"
	exit 1
fi

GCC=$(find_package "gcc")
GCC_VER=$(find_package_gcc_version "gcc")
LIBSTDCPP=$(find_libstdcpp "libstdc++")

install_libstdcpp

msg_green "" "$LIBSTDCPP has been built."

exit 0

