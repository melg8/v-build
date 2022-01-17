#!/bin/bash

cp -v ../v-build_build/io_lib/libio_lib.so.1.0.0 plugins/system/libio_lib.so.1.0.0
cp -v ../v-build_build/navigation_lib/libnavigation_lib.so.1.0.0 plugins/system/libnavigation_lib.so.1.0.0

rm -rfv ../v-build_build/v-build/plugins
mkdir ../v-build_build/v-build/plugins
cp -rv plugins/* ../v-build_build/v-build/plugins
