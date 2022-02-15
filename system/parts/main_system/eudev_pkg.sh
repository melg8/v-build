#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "\n${NC}$1 ${GREEN}$2${NC}\n\n" ; }
function msg_red(){ printf "\n${NC}$1 ${RED}$2${NC}\n\n" ; }

search_pkg=`sh /parts/main_system/find_package.sh "eudev"`

if [ ! -z "${search_pkg}" ]; then
	msg_green "package found:" "$search_pkg"
else
	msg_res "package not found:" "$search_pkg"
	exit 1
fi

pushd /packages/${search_pkg}/${search_pkg}

./configure --prefix=/usr           \
            --bindir=/usr/sbin      \
            --sysconfdir=/etc       \
            --enable-manpages       \
            --disable-static

make

mkdir -pv /usr/lib/udev/rules.d
mkdir -pv /etc/udev/rules.d

make install

udev_lfs_pkg=`sh /parts/main_system/find_package.sh "udev-lfs"`

cp -r /packages/${udev_lfs_pkg}/* /packages/${search_pkg}/${search_pkg}/

make -f ${udev_lfs_pkg}/Makefile.lfs install

popd



udevadm hwdb --update

exit 0


