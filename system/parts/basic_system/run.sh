#!/bin/bash

pushd /parts/basic_system
#./man-pages.sh
#./iana-etc.sh
#./glibc.sh
./zlib.sh
./bzip2.sh
popd

exit 0

