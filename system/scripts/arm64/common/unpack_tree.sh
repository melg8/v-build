#!/bin/bash

if [ ! -d "$V_BUILD_TREE_X86_64" ]; then
	printf "Nothing to pack, maybe env vars aren't set?\n"
	exit 1
else
	if [ -e ".vkfs_mounted" ]; then
		printf "Can't pack the tree, Virtual Kernel FS mounted\n"
		exit 1
	else
		rm -rf $2
		mkdir $2
		pushd $2
		sudo tar -xpf $V_BUILD_DIR/$1
		popd
	fi
fi

exit 0

