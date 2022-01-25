###############################################################################
#
# Linux kernel download and extract script
#
###############################################################################
#!/bin/bash

# -----------------------------------------------------------------------------

if [ $# -ne 2 ]; then
	printf "Incorrect arguments count, exit.\n"
	exit 1
fi

major=$1
version=$2

# -----------------------------------------------------------------------------
# Simple checks
# -----------------------------------------------------------------------------
if [ -z "$major" ]; then
  printf "Error: MAJOR variable not specified, exit.\n"
  exit 1
fi
if [ -z "$version" ]; then
  printf "Error: VERSION variable not specified, exit.\n"
  exit 1
fi

if [ -d "linux-${version}" ]; then
  printf "Error: linux-${version} already exist.\n"
  exit 1
fi

linux_tar="linux-${version}.tar"
linux_tar_path="$PWD/$linux_tar"
linux_tar_xz="${linux_tar}.xz"
linux_tar_xz_path="$PWD/$linux_tar_xz"
linux_site="https://www.kernel.org/pub/linux/kernel"
kernel_url=${linux_site}/${major}/${linux_tar_xz}

# -----------------------------------------------------------------------------
# Download linux
# -----------------------------------------------------------------------------
if [ ! -e ${linux_tar_xz_path} ]; then
  printf "Info: Downloading linux-$version\n"
  wget ${kernel_url}
else
  printf "Info: Linux-$version already downloaded.\n"
fi
# -----------------------------------------------------------------------------
# Decompress tar.xz
# -----------------------------------------------------------------------------
if [ ! -e ${linux_tar_path} ]; then
  printf "Info: Decompressing linux-$version, please wait.\n"
  unxz -k ${linux_tar_xz_path}
  rm -v ${linux_tar_xz_path}
fi
# -----------------------------------------------------------------------------
# Unpack kernel
# -----------------------------------------------------------------------------
printf "Unpacking kernel"
tar -xvf ${linux_tar_path}
rm ${linux_tar_path}
cd "$PWD/linux-${version}" && make mrproper
cd ..

printf "Info: linux kernel preparation successfully completed.\n"


