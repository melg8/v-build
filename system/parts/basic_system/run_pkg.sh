#!/bin/bash

pushd /parts/basic_system
#./man-pages_pkg.sh
#./iana-etc_pkg.sh
#./glibc_pkg.sh
#./zlib_pkg.sh
#./bzip2_pkg.sh
#./xz_pkg.sh
#./zstd_pkg.sh
#./file_pkg.sh
#./ncurses_pkg.sh

# readline after ncurses
#./readline_pkg.sh

#./m4_pkg.sh
#./bc_pkg.sh
#./flex_pkg.sh

# tcl is hard coded script, version - 8.6
#./tcl_pkg.sh

#./expect_pkg.sh
# dejagnu is depend from expect
#./dejagnu_pkg.sh

# binutils is depend from expect
#./binutils_pkg.sh

#./gmp_pkg.sh
#./mpfr_pkg.sh
#./mpc_pkg.sh
#./attr_pkg.sh
#./acl_pkg.sh
#./libcap_pkg.sh
#./shadow_pkg.sh
#./gcc_pkg.sh
#./pkg-config_pkg.sh
./sed_pkg.sh



popd

exit 0

