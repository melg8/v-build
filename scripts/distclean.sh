#!/bin/bash

# Remove build dir
# Remove pkg dir

RED='\033[0;31m'
NC='\033[0m'

rm -rf $V_BUILD_DIR/build/* > /dev/null 2>&1
printf "Directory 'build' ${RED}deleted${NC}\n"

rm -rf $V_BUILD_DIR/pkg/* > /dev/null 2>&1
printf "Directory 'pkg' ${RED}deleted${NC}\n"

rm -rf $V_BUILD_TREE_X86_64
printf "Directory 'tree x86_64' ${RED}deleted${NC}\n"

rm -rf ${V_BUILD_DIR}/.extracted
