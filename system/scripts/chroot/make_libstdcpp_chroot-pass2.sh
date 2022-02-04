#!/bin/bash

# install C++ library

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "\n${NC}$1 ${GREEN}$2${NC}\n\n" ; }
function msg_red(){ printf "\n${NC}$1 ${RED}$2${NC}\n\n" ; }

GCC="none"
ARCH=$(uname -m)-lfs-linux-gnu

############################# Functions ########################################

# find package in PKG dir
function find_package(){
	local search_pkg=$1
	pushd  /packages > /dev/null 2>&1
	local res=$(ls | grep $search_pkg)

	if [ -z "$res" ]; then
		msg_red "Pkg not found:" "$search_pkg"
		popd > /dev/null 2>&1
		exit 1
	else
		echo $res
	fi

	popd > /dev/null 2>&1
}

function install_libstdcpp(){	
	msg_green "Package found: " "$GCC"

	rm -rf /packages/${GCC}/${GCC}/build
	mkdir -pv /packages/${GCC}/${GCC}/build

	pushd  /packages/${GCC}/${GCC} > /dev/null 2>&1
	ln -s gthr-posix.h libgcc/gthr-default.h
	popd > /dev/null 2>&1
	sleep 1

	pushd  /packages/${GCC}/${GCC}/build > /dev/null 2>&1

	sh ../libstdc++-v3/configure     \
    CXXFLAGS="-g -O2 -D_GNU_SOURCE"  \
    --prefix=/usr                    \
    --disable-multilib               \
    --disable-nls                    \
    --host=$ARCH                     \
    --disable-libstdcxx-pch

	make -j`nproc`
	make install

	popd > /dev/null 2>&1
}

#################################### Main ######################################

GCC=$(find_package "gcc")

install_libstdcpp

msg_green "" "libstdc++ has been built."

exit 0

