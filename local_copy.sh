#!/bin/bash

cp -v ../v-build_build/io_lib/libio_lib.so.1.0.0 system/libs/libio_lib.so.1.0.0
cp -v ../v-build_build/navigation_lib/libnavigation_lib.so.1.0.0 system/libs/libnavigation_lib.so.1.0.0

rm -rfv ../v-build_build/v-build/system
mkdir ../v-build_build/v-build/system
cp -rv system/* ../v-build_build/v-build/system

rm -rf ../v-build_run
mkdir ../v-build_run
mkdir ../v-build_run/system
cp -v ../v-build_build/v-build/v-build ../v-build_run/v-build
cp -rv ../v-build_build/v-build/system/* ../v-build_run/system
