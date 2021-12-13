#!/bin/bash

# Install gcc headers

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
PKG_COUNTER=1

function msg(){ printf "${NC}$1 $2${NC}\n" ; }
function msg_green(){ printf "${NC}$1 ${GREEN}$2${NC}" ; }
function msg_red(){ printf "${NC}$1 ${RED}$2${NC}" ; }

$V_BUILD_TOOLS_X86_64/libexec/gcc/$V_BUILD_TGT_X86_64/10.3.0/install-tools/mkheaders | \
	msg_green "\nGCC headers" "installed\n"

exit 0



