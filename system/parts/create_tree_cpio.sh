#!/bin/bash

pushd /

find . | cpio --quiet -o -H newc | bzip2 -c > tree.cpio

popd

exit 0
