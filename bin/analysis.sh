#!/bin/bash

cur=$(dirname $(readlink -f $0))

function plot {
gnuplot << EOF
set terminal png size 1000,300 enhanced font "Helvetica,20"
set term $3
set output '$2.$3'
set ylabel 'time (ms)'
plot '$1/results.dat' using 1 with lines title 'encoding', \
     '$1/results.dat' using 2 with lines title 'decoding'
EOF
}

for exp in $cur/../results/* ; do
	for run in $exp/* ; do
		if [ ! -d $run ] ; then
			continue
		fi
		pushd $run
		tar xjf perf.data.tar.bz2 -C ~/.debug
		perf script -s $cur/perf-script.py > $run/results.dat
		image_path=$cur/../images/eps/$(basename $exp)-$(basename $run)
		plot $run $image_path eps
		image_path=$cur/../images/png/$(basename $exp)-$(basename $run)
		plot $run $image_path png
		popd
	done
	pushd $exp
	$cur/tests.py > tests.txt
	popd
done
exit 0

