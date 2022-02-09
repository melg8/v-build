#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "\n${NC}$1 ${GREEN}$2${NC}\n\n" ; }
function msg_red(){ printf "\n${NC}$1 ${RED}$2${NC}\n\n" ; }

search_pkg=`sh /parts/basic_system/find_package.sh "e2fsprogs"`

if [ ! -z "${search_pkg}" ]; then
	msg_green "package found:" "$search_pkg"
else
	msg_res "package not found:" "$search_pkg"
	exit 1
fi

pushd /packages/${search_pkg}/${search_pkg}

rm -rf build
mkdir build

pushd build

../configure --prefix=/usr           \
             --sysconfdir=/etc       \
             --enable-elf-shlibs     \
             --disable-libblkid      \
             --disable-libuuid       \
             --disable-uuidd         \
             --disable-fsck

make

make install

rm -fv /usr/lib/{libcom_err,libe2p,libext2fs,libss}.a

gunzip -v /usr/share/info/libext2fs.info.gz
install-info --dir-file=/usr/share/info/dir /usr/share/info/libext2fs.info

popd

popd

exit 0


