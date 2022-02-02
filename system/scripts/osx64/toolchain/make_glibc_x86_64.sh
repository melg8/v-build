#!/bin/bash

# Build C library for x86_64 arch

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

GLIBC="none"

################################# Functions ####################################

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "\n${NC}$1 ${GREEN}$2${NC}\n" ; }
function msg_red(){ printf "\n${NC}$1 ${RED}$2${NC}\n" ; }

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

function make_patch(){
	if [ -e ".patched" ]; then
		msg_green "Patch status: " "patched"
	else
		msg_red "Patch status: " "unpatched"
		local patch_file=$(ls ${V_BUILD_PATCH_DIR} | grep -i "glibc")
		if [ -z "$patch_file" ]; then
			msg_red "" "patch file not found!"
			exit 1
		else
			msg_green "Applying patch: " "$patch_file"
			patch -Np1 -i ${V_BUILD_PATCH_DIR}/$patch_file
			touch ".patched"
		fi
			
	fi
}

function install_glibc(){	
	msg_green "Package found: " "$GLIBC"

	if [ -d "${V_BUILD_PKG_DIR}/${GLIBC}/${GLIBC}/build" ]; then
		pushd ${V_BUILD_PKG_DIR}/$GLIBC/$GLIBC/build > /dev/null 2>&1
		make uninstall
		popd > /dev/null 2>&1
	fi

	rm -rfv ${V_BUILD_PKG_DIR}/${GLIBC}/${GLIBC}/build
	mkdir -pv ${V_BUILD_PKG_DIR}/${GLIBC}/${GLIBC}/build

	pushd ${V_BUILD_PKG_DIR}/$GLIBC/$GLIBC > /dev/null 2>&1
	make_patch

	case $(uname -m) in
		i?86)   ln -sfv ld-linux.so.2 $LFS/lib/ld-lsb.so.3
		;;
		x86_64) ln -sfv ../lib/ld-linux-x86-64.so.2 $V_BUILD_TREE_X86_64/lib64
				ln -sfv ../lib/ld-linux-x86-64.so.2 $V_BUILD_TREE_X86_64/lib64/ld-lsb-x86-64.so.3
		;;
	esac

	popd > /dev/null 2>&1

	pushd ${V_BUILD_PKG_DIR}/${GLIBC}/${GLIBC}/build > /dev/null 2>&1

	echo "rootsbindir=/usr/sbin" > configparams

	sh ../configure \
	--prefix=/usr \
	--host=${V_BUILD_TGT_X86_64} \
	--build=$(../scripts/config.guess) \
	--enable-kernel=3.2 \
	--without-selinux \
	--with-headers=${V_BUILD_TREE_X86_64}/usr/include \
	libc_cv_slibdir=/usr/lib

	make -j`nproc`
	make DESTDIR=${V_BUILD_TREE_X86_64} install

	# fix hardcoded path to executable loader in ldd script
	sed '/RTLDLIST=/s@/usr@@g' -i ${V_BUILD_TREE_X86_64}/usr/bin/ldd

	popd > /dev/null 2>&1
}

function check_env(){
	pushd ${V_BUILD_TREE_X86_64} > /dev/null 2>&1

	echo "int main(){}" > check.c
	$V_BUILD_TGT_X86_64-gcc check.c
	
	local temp=$(readelf -l a.out | grep '/ld-linux')
	# remove trailing space at the begining
	local checkline=$(echo $temp | xargs)

	msg_green "Checkline:" "$checkline"

	if [ "$checkline" = "[Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]" ] ; then
		msg_green "Env check: " "good"
	else
		msg_red "Env check: " "bad"
		exit 1
	fi

	rm check.c a.out

	popd > /dev/null 2>&1
}

#################################### Main ######################################

if [ ! -d "${V_BUILD_TOOLS_X86_64}" ]; then
	printf "env variables don't set, exit.\n"
	exit 1
fi

GLIBC=$(find_package "glibc")

install_glibc
check_env

exit 0
