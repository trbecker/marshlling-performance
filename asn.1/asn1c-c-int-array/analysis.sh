#!/bin/bash

for i in 256 512 1024 2048 4096 ; do
	pushd $i
	tar -xjf perf.data.tar.bz2  -C ~/.debug
	perf script -s ../perf-script.py > results.dat
	popd
done

./plot-eps.sh
./tests.py
