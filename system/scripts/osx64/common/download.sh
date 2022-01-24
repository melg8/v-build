#!/bin/bash

# Download all archives and patches

PKG_LIST="$V_BUILD_SYSTEM/scripts/osx64/packages.list"
PATCH_LIST="$V_BUILD_SYSTEM/scripts/osx64/patches.list"

if [ ! -d "$V_BUILD_ARCHIVE_DIR" ]; then
	mkdir $V_BUILD_ARCHIVE_DIR
fi

if [ -d "$V_BUILD_PATCH_DIR" ]; then
	mkdir $V_BUILD_PATCH_DIR
fi

wget --input-file=$PKG_LIST --continue --directory-prefix=$V_BUILD_ARCHIVE_DIR
wget --input-file=$PATCH_LIST --continue --directory-prefix=$V_BUILD_PATCH_DIR

