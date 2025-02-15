#!/bin/sh

cd rebison || exit

for x in html scr scr_sym sproc; do
	$x/rebison >/dev/null <$x.log || exit
done
