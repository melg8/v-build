#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "\n${NC}$1 ${GREEN}$2${NC}\n\n" ; }
function msg_red(){ printf "\n${NC}$1 ${RED}$2${NC}\n\n" ; }

gettext_pkg=`sh /parts/main/temp/find_package.sh "gettext"`

if [ ! -z "${gettext_pkg}" ]; then
	msg_green "package found:" "$gettext_pkg"
else
	msg_res "package not found:" "$gettext_pkg"
	exit 1
fi

pushd /packages/${gettext_pkg}/${gettext_pkg}

./configure --disable-shared
make
cp -v gettext-tools/src/{msgfmt,msgmerge,xgettext} /usr/bin

popd

exit 0


