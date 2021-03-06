#!/bin/sh
# this script was written by Sergio Johann Filho [sergio.johann@acad.pucrs.br]
#
# in order to build the toolchain, we need some basic tools:
# flex bison libgmp3-dev libmpfr-dev autoconf texinfo build-essential libncurses5-dev
#
# you don't need to run this script as root. after completion, just move the
# mips-elf directory to its place (e.g /usr/local) and add the tools directory
# to the PATH environment variable (export $PATH:=$PATH:/usr/local/mips-elf/gcc/bin).
# alternatively, the compiler may be left anywhere in the user home directory. Also, create
# a symbolic link in the mips-elf directory (gcc-9.2.0 -> gcc) to support multiple
# versions of the toolchain.
#
# Use this script if you want do compile the hypervisor with GCC 9.2.0 for MIPS.
#

sudo apt --assume-yes install flex bison libgmp3-dev libmpfr-dev autoconf texinfo build-essential libncurses5-dev libz-dev

binutils_base="binutils-2.34"
gcc_base="gcc-9.2.0"
newlib_base="newlib-3.1.0"
gdb_base="gdb-8.2.1"

root_dir="$HOME/Downloads"

TARGET=mips-elf
PREFIX=${root_dir}/$TARGET/${gcc_base}
BUILD=i686-linux-gnu

# setup our toolchain new path
export PATH=$PREFIX/bin:$PATH

dl_dir="${root_dir}/download"
src_dir="${root_dir}/source"
bld_dir="${root_dir}/build"
install_dir="${root_dir}/install"

mkdir -p ${src_dir}
mkdir -p ${bld_dir}
mkdir -p ${install_dir}
mkdir -p ${dl_dir}

# download all sources
cd $dl_dir
wget -c ftp://ftp.gnu.org/gnu/binutils/${binutils_base}.tar.gz
wget -c ftp://ftp.gnu.org/gnu/gcc/${gcc_base}/${gcc_base}.tar.gz
wget -c ftp://sources.redhat.com/pub/newlib/${newlib_base}.tar.gz
wget -c ftp://ftp.gnu.org/gnu/gdb/${gdb_base}.tar.gz

# unpack everything
cd ${src_dir}
tar -zxvf ${dl_dir}/"${binutils_base}.tar.gz"
tar -zxvf ${dl_dir}/"${gcc_base}.tar.gz"
tar -zxvf ${dl_dir}/"${newlib_base}.tar.gz"
tar -zxvf ${dl_dir}/"${gdb_base}.tar.gz"

#
# build binutils
#
cd ${bld_dir}
mkdir ${binutils_base}
cd ${binutils_base}
${src_dir}/${binutils_base}/configure --prefix=$PREFIX --target=$TARGET --with-sysroot --disable-nls --disable-werror
make -j2 all
make install

#
# build GCC
#
cd ${src_dir}/${gcc_base}
./contrib/download_prerequisites

cd ${bld_dir}
mkdir ${gcc_base}
cd ${gcc_base}
${src_dir}/${gcc_base}/configure --prefix=$PREFIX --target=$TARGET \
	--disable-nls --enable-languages=c \
	--enable-interwork --enable-multilib --with-system-zlib --with-newlib \
	--disable-shared --without-headers
make -j2 all-gcc
make install-gcc

#
# build newlib
#
cd ${bld_dir}
mkdir ${newlib_base}
cd ${newlib_base}
${src_dir}/${newlib_base}/configure --prefix=$PREFIX --target=$TARGET \
	--disable-nls --enable-interwork \
	--enable-multilib --disable-newlib-supplied-syscalls
make -j2 all
make install

#
# build final GCC
#
cd ${bld_dir}
cd ${gcc_base}
${src_dir}/${gcc_base}/configure --prefix=$PREFIX --target=$TARGET \
	--disable-nls --enable-languages=c,c++ \
	--enable-interwork --enable-multilib --with-system-zlib --with-newlib \
	--disable-shared
make -j2 all
make install

#
# build GDB
#
cd ${bld_dir}
mkdir ${gdb_base}
cd ${gdb_base}
${src_dir}/${gdb_base}/configure --prefix=$PREFIX --target=$TARGET \
 --enable-interwork --enable-multilib
make -j2 all
make install

sudo mv ${root_dir}/$TARGET /opt

rm -rf ${src_dir}
rm -rf ${bld_dir}
rm -rf ${install_dir}
rm -rf ${dl_dir}

echo  >> ~/.profile
echo "export PATH=\"\$PATH:\"/opt/$TARGET/gcc-9.2.0/bin\"\"" >> ~/.profile
echo  >> ~/.profile

echo "***********************************************************"
echo "You need to logout to the changes on you PATH make effect. "
echo "***********************************************************"



