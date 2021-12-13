#!/bin/bash

# clean all packages in $V_BUILD_BUILD_DIR

RED='\033[0;31m'
NC='\033[0m'
PKG_COUNTER=1

if [ -e "$V_BUILD_BUILD_DIR" ]; then
	pushd $V_BUILD_BUILD_DIR > /dev/null 2>&1

	for pkg in *; do
		if [ -d "$pkg" ]; then
			rm -rf $pkg/* > /dev/null 2>&1
		fi
		printf "($PKG_COUNTER) ${RED}Cleaning:${NC} $pkg\n"
		let "PKG_COUNTER=PKG_COUNTER+1"
	done

	popd > /dev/null 2>&1
fi

exit 0
