#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "\n${NC}$1 ${GREEN}$2${NC}\n\n" ; }
function msg_red(){ printf "\n${NC}$1 ${RED}$2${NC}\n\n" ; }

search_pkg=`sh /parts/temp_system/find_package.sh "perl"`
ver=`echo ${search_pkg:5:4}`

if [ ! -z "${search_pkg}" ]; then
	msg_green "package found:" "$search_pkg"
else
	msg_res "package not found:" "$search_pkg"
	exit 1
fi

pushd /packages/${search_pkg}/${search_pkg}

sh Configure -des                                        \
             -Dprefix=/usr                               \
             -Dvendorprefix=/usr                         \
             -Dprivlib=/usr/lib/perl5/$ver/core_perl     \
             -Darchlib=/usr/lib/perl5/$ver/core_perl     \
             -Dsitelib=/usr/lib/perl5/$ver/site_perl     \
             -Dsitearch=/usr/lib/perl5/$ver/site_perl    \
             -Dvendorlib=/usr/lib/perl5/$ver/vendor_perl \
             -Dvendorarch=/usr/lib/perl5/$ver/vendor_perl

make
make install


popd

exit 0


