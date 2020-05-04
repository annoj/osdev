#!/bin/sh
set -e
# . ./headers.sh
. ./config.sh

for PROJECT in $PROJECTS; do
	(cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install)
done
