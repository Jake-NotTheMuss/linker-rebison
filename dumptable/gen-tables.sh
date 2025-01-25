#!/bin/sh

linker=${TA_GAME_PATH}bin/linker_modtools.exe

outdir=

dir=`dirname "$0"`

while test "x$1" != x; do
	case $1 in
		-o|--outdir) shift; outdir=$1;;
		-o=*|--outdir=*) outdir=${1#*=};;
		*) echo "invalid argument"; exit 1;;
	esac
	shift
done

if test "x$outdir" = x; then
	outdir=`cd "$dir/../rebison" && pwd`
fi

make -C "$dir" clean || exit

make -C "$dir" OUTDIR=$outdir || exit

make -C "$dir" install || exit

"$linker" -version

make -C "$dir" uninstall
