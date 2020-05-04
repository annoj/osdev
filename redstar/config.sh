export OSNAME=redstar

SYSTEM_HEADER_PROJECTS="kernel"
PROJECTS="kernel"

CROSSDIR=/home/jona/bin/cross/bin

export HOST=${HOST:-$(./host.sh)}
export MAKE=/usr/bin/make

export AR=${CROSSDIR}${HOST}-ar
export AS=${CROSSDIR}${HOST}-as
export CC=${CROSSDIR}${HOST}-gcc

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export CFLAGS='-O2 -g'

# Configure the cross-compiler to use the desired system root.
export SYSROOT="$(pwd)/sysroot"
export CC="$CC --sysroot=$SYSROOT"

# Work around that the -elf gcc targets doesn't have a system include directory
# because it was configured with --without-headers rather than --with-sysroot.
if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
	export CC="$CC -isystem=$INCLUDEDIR"
fi
