#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
PKG_COUNTER=1

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "\n${NC}$1 ${GREEN}$2${NC}\n" ; }
function msg_red(){ printf "\n${NC}$1 ${RED}$2${NC}\n" ; }

if [ ! -d "${V_BUILD_TREE_X86_64}" ]; then
	msg_red "\$V_BUILD_TREE" "do not exist!"
	exit 1
fi

rm -rf "${V_BUILD_TREE_X86_64}/archives"
sudo rm -rf "${V_BUILD_TREE_X86_64}/packages"
mkdir -pv "${V_BUILD_TREE_X86_64}/packages"
cp -r "${V_BUILD_ARCHIVE_DIR}" "${V_BUILD_TREE_X86_64}/"

sync

for archive in ${V_BUILD_TREE_X86_64}/archives/*.*; do

	# get archive name without full path
	pkg_name=$(basename "$archive")

	# remove 'tar.*' extension
	dirname=$(echo "${V_BUILD_TREE_X86_64}/packages/$pkg_name" | sed 's/\.tar.*//')

	if [ -d "$dirname" ]; then
		msg_green "Directory $dirname already" "exist\n"
		continue
	else
		mkdir $dirname
		# untar into pkg dir
		msg_green "- $PKG_COUNTER - $(basename "$dirname")" "+"
		tar -xf $archive -C "$dirname" > /dev/null 2>&1

		let "PKG_COUNTER=PKG_COUNTER+1"
	fi

done

if [ ! -d "${V_BUILD_KERNEL_X86_64}" ]; then
	msg_red "\$V_BUILD_KERNEL_X86_64" "do not exist!"
	exit 1
else
	cp -r "${V_BUILD_KERNEL_X86_64}" "${V_BUILD_TREE_X86_64}/"
fi

sync

msg_green "copy archives in tree:" "done."

exit 0


