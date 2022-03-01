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

GCC="none"
GCC_VER="none"

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "\n${NC}$1 ${GREEN}$2${NC}\n" ; }
function msg_red(){ printf "\n${NC}$1 ${RED}$2${NC}\n" ; }

# determind arch type
ARCH=$V_BUILD_TGT_X86_64

################################## Functions ###################################

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

# exctract package
function gcc_extract_archive(){
	local pkg_name="$(find_package "$1")"
	local pkg_path="$V_BUILD_PKG_DIR/$GCC/$GCC/$pkg_name"
	if [ ! -d "$pkg_path" ]; then
		local temp=$(ls "$V_BUILD_ARCHIVE_DIR" | grep "${pkg_name}")
		msg_green "Extracting: " "$pkg_name"
		tar -xf "$V_BUILD_ARCHIVE_DIR/$temp" 
		mv "$pkg_name" "$1"
	fi
}

# build GCC - PASS 2
function install_gcc_pass_2(){
	msg_green "Pkg found:" $GCC

	pushd $V_BUILD_PKG_DIR/$GCC/$GCC
	rm -rf mpfr gmp mpc build

	# C lib, multiple precision floatig point computaion
	gcc_extract_archive "mpfr"

	# C lib, arbitrary precision floatig point computaion
	gcc_extract_archive "gmp"

	# arithmetics of complex numbers
	gcc_extract_archive "mpc"

	# On x86_64 hosts, set the default directory name for 64-bit libraries to “lib”
	case $(uname -m) in
		x86_64)
			sed -e '/m64=/s/lib64/lib/' \
			-i.orig gcc/config/i386/t-linux64
		;;
	esac

	mkdir build

	popd

	pushd $V_BUILD_PKG_DIR/$GCC/$GCC/build

	mkdir -pv $ARCH/libgcc
	ln -sv $V_BUILD_PKG_DIR/$GCC/$GCC/libgcc/gthr-posix.h $ARCH/libgcc/gthr-default.h

	sh ../configure \
		--build=$(../config.guess) \
		--with-build-sysroot=$V_BUILD_TREE_X86_64 \
		--host=$ARCH \
		--prefix=/usr \
		CC_FOR_TARGET=$ARCH-gcc \
		--enable-initfini-array \
		--disable-nls \
		--disable-multilib \
		--disable-decimal-float \
		--disable-libatomic \
		--disable-libgomp \
		--disable-libquadmath \
		--disable-libssp \
		--disable-libvtv \
		--disable-libstdcxx \
		--enable-languages=c,c++

	make -j`nproc`
	make DESTDIR=${V_BUILD_TREE_X86_64} install

	popd

	pushd ${V_BUILD_TREE_X86_64}/bin
	ln -sv gcc $V_BUILD_TREE_X86_64/usr/bin/cc
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

msg_green "Making GCC" "PASS 2"

GCC=$(find_package "gcc")
GCC_VER=$(find_package_gcc_version "gcc")

msg "$GCC"

install_gcc_pass_2

msg_green "" "GCC-pass 2 has been built."

exit 0

