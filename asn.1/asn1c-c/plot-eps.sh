#!/bin/bash

function plot {
gnuplot << EOF
set terminal png size 1000,300 enhanced font "Helvetica,20"
set term eps
set output 'asn1_int_array_$1_elements.eps'
set ylabel 'time (ms)'
plot '$1/results.dat' using 1 with lines title 'encoding', \
     '$1/results.dat' using 2 with lines title 'decoding'
EOF
}

for i in 256 512 1024 2048 4096 ; do
	plot $i
done
