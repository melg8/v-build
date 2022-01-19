#!/bin/bash

cp -v ../v-build_build/io_lib/libio_lib.so.1.0.0 system/libs/libio_lib.so.1.0.0
cp -v ../v-build_build/navigation_lib/libnavigation_lib.so.1.0.0 system/libs/libnavigation_lib.so.1.0.0

rm -rfv ../v-build_build/v-build/system
mkdir ../v-build_build/v-build/system
cp -rv system/* ../v-build_build/v-build/system
