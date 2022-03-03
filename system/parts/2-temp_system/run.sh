#!/bin/bash

pushd /parts/2-temp_system
./gettext.sh
./bison.sh
./perl.sh
./python3.sh
./texinfo.sh
./util-linux.sh
./clean.sh
popd

exit 0

