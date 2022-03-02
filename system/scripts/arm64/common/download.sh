#!/bin/bash

# Download all archives and patches

PKG_LIST="$V_BUILD_SYSTEM/scripts/osx64/packages.list"
PATCH_LIST="$V_BUILD_SYSTEM/scripts/osx64/patches.list"

if [ ! -d "$V_BUILD_ARCHIVE_DIR" ]; then
	printf "Directory for archives doesn't exist, check env variables\n"
	exit 1
fi

if [ ! -d "$V_BUILD_PATCH_DIR" ]; then
	printf "Directory for patches doesn't exist, check env variables\n"
	exit 1
fi

wget --input-file=$PKG_LIST --continue --directory-prefix=$V_BUILD_ARCHIVE_DIR
wget --input-file=$PATCH_LIST --continue --directory-prefix=$V_BUILD_PATCH_DIR

