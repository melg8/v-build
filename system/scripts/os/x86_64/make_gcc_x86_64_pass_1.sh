#!/bin/bash

# Create toolchain:
# linker, assembler, compiler
#
# Arch:
# x86_64

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
COUNTER=1

GCC="none"

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

# build GCC - PASS 1
function install_gcc_pass_1(){
	msg_green "Pkg found:" $GCC
	
	rm -rf $V_BUILD_BUILD_DIR/$GCC
	mkdir -p $V_BUILD_BUILD_DIR/$GCC

	pushd $V_BUILD_PKG_DIR/$GCC/$GCC
	rm -rf mpfr gmp mpc

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

	popd

	pushd $V_BUILD_BUILD_DIR/$GCC
	sh $V_BUILD_PKG_DIR/$GCC/$GCC/configure \
	--target=$ARCH \
	--prefix=$V_BUILD_TOOLS_X86_64 \
	--with-glibc-version=2.11 \
	--with-sysroot=$V_BUILD_TREE_X86_64 \
	--with-newlib \
	--without-headers \
	--enable-initfini-array \
	--disable-nls \
	--disable-bootstrap \
	--disable-shared \
	--disable-multilib \
	--disable-decimal-float \
	--disable-threads \
	--disable-libatomic \
	--disable-libgomp \
	--disable-libquadmath \
	--disable-libssp \
	--disable-libvtv \
	--disable-libstdcxx \
	--enable-languages=c,c++

	make -j`nproc`
	make install -j1
	popd

}

################################## Main ########################################

if [ ! -f "${V_BUILD_DIR}/.extracted" ]; then
	msg_red "Packages are" "not extracted!"
	msg "Run: make extract\n"
	exit 1
elif [ ! -d "${V_BUILD_TREE_X86_64}" ]; then
	msg_red "V BUILD TREE" "do not exist!"
	msg "Run: make os-tree-x86_64\n"
	exit 1
else
	GCC=$(find_package "gcc")

	install_gcc_pass_1

	pushd $V_BUILD_PKG_DIR/$GCC/$GCC
	cat gcc/limitx.h gcc/glimits.h gcc/limity.h > \
		`dirname $($V_BUILD_TOOLS_X86_64/bin/$ARCH-gcc -print-libgcc-file-name)`/install-tools/include/limits.h
	msg_green "" "limits.h updated."
	popd

	msg_green "" "GCC-pass 1 has been built."
fi

exit 0

