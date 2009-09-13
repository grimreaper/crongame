#!/usr/bin/env sh
pkg_info -e allegro-4.2.2_2;
if [ $? -eq 0 ];
then
else
	./scripts/rootcheck.sh
	val=$?
	if [ $val -ne 0 ];
	then
		return $val;
	fi;
	val=$(pkg_info -e allegro);
	if [ $val -ne 0 ]
	then
		make -C /usr/ports/devel/allegro install distclean
	fi
fi;
