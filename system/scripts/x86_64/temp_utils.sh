#!/bin/bash

# installation:

# m4 - macrorocessor
# ncurses
# bash
# coreutils
# diffutils
# file


GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "\n${NC}$1 ${GREEN}$2${NC}\n\n" ; }
function msg_red(){ printf "\n${NC}$1 ${RED}$2${NC}\n\n" ; }

M4="none"
NCURSES="none"
BASHPKG="none"
COREUTILS="none"
DIFFUTILS="none"
FILEPKG="none"
FINDPKG="none"
GAWK="none"
GREPPKG="none"
GZIP="none"
MAKEPKG="none"
PATCHPKG="none"
SEDPKG="none"
TARPKG="none"
XZPKG="none"

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


function install_m4(){
	msg_green "Package found: " "$M4"

	if [ -e "${V_BUILD_BUILD_DIR}/$M4/Makefile" ]; then
		pushd ${V_BUILD_BUILD_DIR}/$M4
		make DESTDIR=${V_BUILD_TREE_X86_64} uninstall
		popd
	fi

	rm -rf ${V_BUILD_BUILD_DIR}/${M4}
	mkdir ${V_BUILD_BUILD_DIR}/${M4}

	pushd ${V_BUILD_BUILD_DIR}/$M4

	sh ${V_BUILD_PKG_DIR}/$M4/$M4/configure \
	--prefix=/usr \
	--host=${V_BUILD_TGT_X86_64} \
	--build=$(${V_BUILD_PKG_DIR}/$M4/$M4/build-aux/config.guess)

	make -j`nproc`
	make DESTDIR=${V_BUILD_TREE_X86_64} install

	msg_green "" "$M4 has been built."

	popd
}

function install_ncurses() {
	msg_green "Package found: " "$NCURSES"

	if [ -e "${V_BUILD_BUILD_DIR}/$NCURSES/Makefile" ]; then
		pushd ${V_BUILD_BUILD_DIR}/$NCURSES
		make DESTDIR=${V_BUILD_TREE_X86_64} uninstall
		popd
	fi

	rm -rf ${V_BUILD_BUILD_DIR}/${NCURSES}
	mkdir ${V_BUILD_BUILD_DIR}/${NCURSES}

	pushd ${V_BUILD_BUILD_DIR}/$NCURSES

	sh ${V_BUILD_PKG_DIR}/$NCURSES/$NCURSES/configure

	make -C inslude
	make -C progs tic

	sh configure \
	--prefix=/usr \
	--host=$V_BUILD_TGT_X86_64 \
	--build=$(./config.guess) \
	--mandir=/usr/share/man \
	--with-manpage-format=normal \
	--with-shared \
	--without-debug \
	--without-ada \
	--without-normal \
	--enable-widec

	make -j`nproc`
	make DESTDIR=${V_BUILD_TREE_X86_64} TIC_PATH=${pwd}/build/progs/tic install

	echo "INPUT(-lncursesw)" > ${V_BUILD_TREE_X86_64}/usr/lib/libncurses.so

	msg_green "" "$NCURSES has been built."

	popd
}

function install_bash(){
	msg_green "Package found: " "$BASHPKG"

	if [ -e "${V_BUILD_BUILD_DIR}/$BASHPKG/Makefile" ]; then
		pushd ${V_BUILD_BUILD_DIR}/$BASHPKG
		make DESTDIR=${V_BUILD_TREE_X86_64} uninstall
		unlink ${V_BUILD_TREE_X86_64}/usr/bin/sh
		popd
	fi

	rm -rf ${V_BUILD_BUILD_DIR}/${BASHPKG}
	mkdir ${V_BUILD_BUILD_DIR}/${BASHPKG}

	pushd ${V_BUILD_BUILD_DIR}/$BASHPKG

	sh ${V_BUILD_PKG_DIR}/$BASHPKG/$BASHPKG/configure \
	--prefix=/usr \
	--build=$(${V_BUILD_PKG_DIR}/$BASHPKG/$BASHPKG/support/config.guess) \
	--host=$V_BUILD_TGT_X86_64 \
	--without-bash-malloc

	make -j`nproc`
	make DESTDIR=${V_BUILD_TREE_X86_64} install

	popd

	pushd ${V_BUILD_TREE_X86_64}
	ln -s bash usr/bin/sh
	popd

	msg_green "" "$BASHPKG has been built."
}

function install_coreutils(){
	msg_green "Package found: " "$COREUTILS"

	if [ -e "${V_BUILD_BUILD_DIR}/$COREUTILS/Makefile" ]; then
		pushd ${V_BUILD_BUILD_DIR}/$COREUTILS
		make DESTDIR=${V_BUILD_TREE_X86_64} uninstall
		unlink ${V_BUILD_TREE_X86_64}/usr/bin/sh
		popd
	fi

	rm -rf ${V_BUILD_BUILD_DIR}/${COREUTILS}
	mkdir ${V_BUILD_BUILD_DIR}/${COREUTILS}

	pushd ${V_BUILD_BUILD_DIR}/$COREUTILS

	sh ${V_BUILD_PKG_DIR}/$COREUTILS/$COREUTILS/configure \
	--prefix=/usr \
	--host=$V_BUILD_TGT_X86_64 \
	--build=$(${V_BUILD_PKG_DIR}/$COREUTILS/$COREUTILS/build-aux/config.guess)  \
	--enable-install-program=hostname \
	--enable-no-install-program=kill,uptime

	make -j`nproc`
	make DESTDIR=${V_BUILD_TREE_X86_64} install

	popd

	pushd ${V_BUILD_TREE_X86_64}

	mv -v ${V_BUILD_TREE_X86_64}/usr/bin/chroot ${V_BUILD_TREE_X86_64}/usr/sbin
	mkdir -p ${V_BUILD_TREE_X86_64}/usr/share/man/man8
	mv -v ${V_BUILD_TREE_X86_64}/usr/share/man/man1/chroot.1 \
		${V_BUILD_TREE_X86_64}/usr/share/man/man8/chroot.8
	sed -i 's/"1"/"8"/' ${V_BUILD_TREE_X86_64}/usr/share/man/man8/chroot.8

	popd

	msg_green "" "$COREUTILS has been built."
}

function install_diffutils(){
	msg_green "Package found: " "$DIFFUTILS"

	if [ -e "${V_BUILD_BUILD_DIR}/$DIFFUTILS/Makefile" ]; then
		pushd ${V_BUILD_BUILD_DIR}/$DIFFUTILS
		make DESTDIR=${V_BUILD_TREE_X86_64} uninstall
		unlink ${V_BUILD_TREE_X86_64}/usr/bin/sh
		popd
	fi

	rm -rf ${V_BUILD_BUILD_DIR}/${DIFFUTILS}
	mkdir ${V_BUILD_BUILD_DIR}/${DIFFUTILS}

	pushd ${V_BUILD_BUILD_DIR}/$DIFFUTILS

	sh ${V_BUILD_PKG_DIR}/$DIFFUTILS/$DIFFUTILS/configure \
	--prefix=/usr \
	--host=$V_BUILD_TGT_X86_64

	make -j`nproc`
	make DESTDIR=${V_BUILD_TREE_X86_64} install

	popd

	msg_green "" "$DIFFUTILS has been built."
}

function install_file(){
	msg_green "Package found: " "$FILEPKG"

	if [ -e "${V_BUILD_BUILD_DIR}/$FILEPKG/Makefile" ]; then
		pushd ${V_BUILD_BUILD_DIR}/$FILEPKG
		make DESTDIR=${V_BUILD_TREE_X86_64} uninstall
		unlink ${V_BUILD_TREE_X86_64}/usr/bin/sh
		popd
	fi

	rm -rf ${V_BUILD_BUILD_DIR}/${FILEPKG}
	mkdir ${V_BUILD_BUILD_DIR}/${FILEPKG}

	pushd ${V_BUILD_BUILD_DIR}/$FILEPKG

	sh ${V_BUILD_PKG_DIR}/$FILEPKG/$FILEPKG/configure \
	--disable-bzlib \
	--disable-libseccomp \
	--disable-xzlib \
	--disable-zlib

	make -j`nproc`

	sh configure \
	--prefix=/usr \
	--host=$V_BUILD_TGT_X86_64 \
	--build=$(./config.guess)

	make FILE_COMPILE=$(pwd)/src/file
	make DESTDIR=${V_BUILD_TREE_X86_64} install

	popd

	msg_green "" "$FILEPKG has been built."
}

function install_find(){
	msg_green "Package found: " "$FINDPKG"

	if [ -e "${V_BUILD_BUILD_DIR}/$FINDPKG/Makefile" ]; then
		pushd ${V_BUILD_BUILD_DIR}/$FINDPKG
		make DESTDIR=${V_BUILD_TREE_X86_64} uninstall
		unlink ${V_BUILD_TREE_X86_64}/usr/bin/sh
		popd
	fi

	rm -rf ${V_BUILD_BUILD_DIR}/${FINDPKG}
	mkdir ${V_BUILD_BUILD_DIR}/${FINDPKG}

	pushd ${V_BUILD_BUILD_DIR}/$FINDPKG

	sh ${V_BUILD_PKG_DIR}/$FINDPKG/$FINDPKG/configure \
	--prefix=/usr \
	--localstatedir=/var/lib/locate \
	--host=$V_BUILD_TGT_X86_64 \
	--build=$(${V_BUILD_PKG_DIR}/$FINDPKG/$FINDPKG/build-aux/config.guess)

	make -j`nproc`

	make DESTDIR=${V_BUILD_TREE_X86_64} install

	popd

	msg_green "" "$FINDPKG has been built."
}

function install_gawk(){
	msg_green "Package found: " "$GAWK"

	if [ -e "${V_BUILD_BUILD_DIR}/$GAWK/Makefile" ]; then
		pushd ${V_BUILD_BUILD_DIR}/$GAWK
		make DESTDIR=${V_BUILD_TREE_X86_64} uninstall
		unlink ${V_BUILD_TREE_X86_64}/usr/bin/sh
		popd
	fi

	rm -rf ${V_BUILD_BUILD_DIR}/${GAWK}
	mkdir ${V_BUILD_BUILD_DIR}/${GAWK}

	pushd ${V_BUILD_BUILD_DIR}/$GAWK

	sh ${V_BUILD_PKG_DIR}/$GAWK/$GAWK/configure \
	--prefix=/usr \
	--host=$V_BUILD_TGT_X86_64 \
	--build=$(${V_BUILD_PKG_DIR}/$GAWK/$GAWK/config.guess)

	make -j`nproc`

	make DESTDIR=${V_BUILD_TREE_X86_64} install

	popd

	msg_green "" "$GAWK has been built."
}

function install_grep(){
	msg_green "Package found: " "$GREPPKG"

	if [ -e "${V_BUILD_BUILD_DIR}/$GREPPKG/Makefile" ]; then
		pushd ${V_BUILD_BUILD_DIR}/$GREPPKG
		make DESTDIR=${V_BUILD_TREE_X86_64} uninstall
		unlink ${V_BUILD_TREE_X86_64}/usr/bin/sh
		popd
	fi

	rm -rf ${V_BUILD_BUILD_DIR}/${GREPPKG}
	mkdir ${V_BUILD_BUILD_DIR}/${GREPPKG}

	pushd ${V_BUILD_BUILD_DIR}/$GREPPKG

	sh ${V_BUILD_PKG_DIR}/$GREPPKG/$GREPPKG/configure \
	--prefix=/usr \
	--host=$V_BUILD_TGT_X86_64

	make -j`nproc`

	make DESTDIR=${V_BUILD_TREE_X86_64} install

	popd

	msg_green "" "$GREPPKG has been built."
}

function install_gzip(){
	msg_green "Package found: " "$GZIP"

	if [ -e "${V_BUILD_BUILD_DIR}/$GZIP/Makefile" ]; then
		pushd ${V_BUILD_BUILD_DIR}/$GZIP
		make DESTDIR=${V_BUILD_TREE_X86_64} uninstall
		unlink ${V_BUILD_TREE_X86_64}/usr/bin/sh
		popd
	fi

	rm -rf ${V_BUILD_BUILD_DIR}/${GZIP}
	mkdir ${V_BUILD_BUILD_DIR}/${GZIP}

	pushd ${V_BUILD_BUILD_DIR}/$GZIP

	sh ${V_BUILD_PKG_DIR}/$GZIP/$GZIP/configure \
	--prefix=/usr \
	--host=$V_BUILD_TGT_X86_64

	make -j`nproc`

	make DESTDIR=${V_BUILD_TREE_X86_64} install

	popd

	msg_green "" "$GZIP has been built."
}

function install_make(){
	msg_green "Package found: " "$MAKEPKG"

	if [ -e "${V_BUILD_BUILD_DIR}/$MAKEPKG/Makefile" ]; then
		pushd ${V_BUILD_BUILD_DIR}/$MAKEPKG
		make DESTDIR=${V_BUILD_TREE_X86_64} uninstall
		unlink ${V_BUILD_TREE_X86_64}/usr/bin/sh
		popd
	fi

	rm -rf ${V_BUILD_BUILD_DIR}/${MAKEPKG}
	mkdir ${V_BUILD_BUILD_DIR}/${MAKEPKG}

	pushd ${V_BUILD_BUILD_DIR}/${MAKEPKG}

	sh ${V_BUILD_PKG_DIR}/$MAKEPKG/$MAKEPKG/configure \
	--prefix=/usr \
	--without-guild \
	--host=$V_BUILD_TGT_X86_64 \
	--build=$(${V_BUILD_PKG_DIR}/$MAKEPKG/$MAKEPKG/build-aux/config.guess)

	make -j`nproc`

	make DESTDIR=${V_BUILD_TREE_X86_64} install

	popd

	msg_green "" "$MAKEPKG has been built."
}

function install_patch(){
	msg_green "Package found: " "$PATCHPKG"

	if [ -e "${V_BUILD_BUILD_DIR}/$PATCHPKG/Makefile" ]; then
		pushd ${V_BUILD_BUILD_DIR}/$PATCHPKG
		make DESTDIR=${V_BUILD_TREE_X86_64} uninstall
		unlink ${V_BUILD_TREE_X86_64}/usr/bin/sh
		popd
	fi

	rm -rf ${V_BUILD_BUILD_DIR}/${PATCHPKG}
	mkdir ${V_BUILD_BUILD_DIR}/${PATCHPKG}

	pushd ${V_BUILD_BUILD_DIR}/${PATCHPKG}

	sh ${V_BUILD_PKG_DIR}/$PATCHPKG/$PATCHPKG/configure \
	--prefix=/usr \
	--host=$V_BUILD_TGT_X86_64 \
	--build=$(${V_BUILD_PKG_DIR}/$PATCHPKG/$PATCHPKG/build-aux/config.guess)

	make -j`nproc`

	make DESTDIR=${V_BUILD_TREE_X86_64} install

	popd

	msg_green "" "$PATCHPKG has been built."
}

function install_sed(){
	msg_green "Package found: " "$SEDPKG"

	if [ -e "${V_BUILD_BUILD_DIR}/$SEDPKG/Makefile" ]; then
		pushd ${V_BUILD_BUILD_DIR}/$SEDPKG
		make DESTDIR=${V_BUILD_TREE_X86_64} uninstall
		unlink ${V_BUILD_TREE_X86_64}/usr/bin/sh
		popd
	fi

	rm -rf ${V_BUILD_BUILD_DIR}/${SEDPKG}
	mkdir ${V_BUILD_BUILD_DIR}/${SEDPKG}

	pushd ${V_BUILD_BUILD_DIR}/${SEDPKG}

	sh ${V_BUILD_PKG_DIR}/$SEDPKG/$SEDPKG/configure \
	--prefix=/usr \
	--host=$V_BUILD_TGT_X86_64

	make -j`nproc`

	make DESTDIR=${V_BUILD_TREE_X86_64} install

	popd

	msg_green "" "$SEDPKG has been built."
}

function install_tar(){
	msg_green "Package found: " "$TARPKG"

	if [ -e "${V_BUILD_BUILD_DIR}/$TARPKG/Makefile" ]; then
		pushd ${V_BUILD_BUILD_DIR}/$TARPKG
		make DESTDIR=${V_BUILD_TREE_X86_64} uninstall
		unlink ${V_BUILD_TREE_X86_64}/usr/bin/sh
		popd
	fi

	rm -rf ${V_BUILD_BUILD_DIR}/${TARPKG}
	mkdir ${V_BUILD_BUILD_DIR}/${TARPKG}

	pushd ${V_BUILD_BUILD_DIR}/${TARPKG}

	sh ${V_BUILD_PKG_DIR}/$TARPKG/$TARPKG/configure \
	--prefix=/usr \
	--host=$V_BUILD_TGT_X86_64 \
	--build=$(${V_BUILD_PKG_DIR}/$TARPKG/$TARPKG/build-aux/config.guess)

	make -j`nproc`

	make DESTDIR=${V_BUILD_TREE_X86_64} install

	popd

	msg_green "" "$TARPKG has been built."
}

function install_xz(){
	msg_green "Package found: " "$XZPKG"

	if [ -e "${V_BUILD_BUILD_DIR}/$XZPKG/Makefile" ]; then
		pushd ${V_BUILD_BUILD_DIR}/$XZPKG
		make DESTDIR=${V_BUILD_TREE_X86_64} uninstall
		unlink ${V_BUILD_TREE_X86_64}/usr/bin/sh
		popd
	fi

	rm -rf ${V_BUILD_BUILD_DIR}/${XZPKG}
	mkdir ${V_BUILD_BUILD_DIR}/${XZPKG}

	pushd ${V_BUILD_BUILD_DIR}/${XZPKG}

	sh ${V_BUILD_PKG_DIR}/$XZPKG/$XZPKG/configure \
	--prefix=/usr \
	--host=$V_BUILD_TGT_X86_64 \
	--build=$(${V_BUILD_PKG_DIR}/$XZPKG/$XZPKG/build-aux/config.guess) \
	--disable-static \
	--docdir=/usr/share/doc/$XZPKG

	make -j`nproc`

	make DESTDIR=${V_BUILD_TREE_X86_64} install

	popd

	msg_green "" "$XZPKG has been built."
}

################################### Main #######################################

M4=$(find_package "m4")
NCURSES=$(find_package "ncurses")
BASHPKG=$(find_package "bash")
COREUTILS=$(find_package "coreutils")
DIFFUTILS=$(find_package "diffutils")
FILEPKG=$(find_package "file")
FINDPKG=$(find_package "findutils")
GAWK=$(find_package "gawk")
GREPPKG=$(find_package "grep")
GZIP=$(find_package "gzip")
MAKEPKG=$(find_package "make" | awk '{print $2}')
PATCHPKG=$(find_package "patch")
SEDPKG=$(find_package "sed")
TARPKG=$(find_package "tar")
XZPKG=$(find_package "xz")

install_m4
install_ncurses
install_bash
install_coreutils
install_diffutils
install_file
install_find
install_gawk
install_grep
install_gzip
install_make
install_patch
install_sed
install_tar
install_xz

exit 0
