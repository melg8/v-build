#!/bin/bash

if [ ! -d "$V_BUILD_TREE_X86_64" ]; then
	printf "Nothing to save, maybe env vars aren't set?\n"
	exit 1
else
	if [ -e ".vkfs_mounted" ]; then
		printf "Can't save the tree, Virtual Kernel FS mounted\n"
		exit 1
	else
		pushd $V_BUILD_TREE_X86_64
		sudo tar -cJpf $V_BUILD_DIR/osx64_temp_tree.tar.xz .
		popd
	fi
fi

exit 0

