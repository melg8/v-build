#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "\n${NC}$1 ${GREEN}$2${NC}\n\n" ; }
function msg_red(){ printf "\n${NC}$1 ${RED}$2${NC}\n\n" ; }

if [ ! -d "${V_BUILD_TREE_X86_64}" ]; then
	msg_red "\$V_BUILD_TREE" "do not exist!"
	exit 1
fi

msg_green "changin ownerships of : " "${V_BUILD_TREE_X86_64}"

sudo chown -R root:root ${V_BUILD_TREE_X86_64}/{usr,lib,var,etc,bin,sbin,tools}
sudo chown -R root:root ${V_BUILD_TREE_X86_64}/lib64

ls -lah ${V_BUILD_TREE_X86_64}

msg_green "status:" "done"

exit 0


