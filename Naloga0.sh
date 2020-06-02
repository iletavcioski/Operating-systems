#!/bin/bash

case $1 in 
	(eho)
	shift
	echo -e $*;
	;;
	(smisel)
	shift
	echo -e "Zivljenje je lepo, ce programiras.";
	exit 42;
	;;
	(macka)
	cat;
	;;
	(*)
	echo -n "Podaj argumente prijatelj.";
	exit 1;
esac
exit
