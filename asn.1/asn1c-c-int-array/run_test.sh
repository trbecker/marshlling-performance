#!/bin/bash

function mtest {
	pushd $1
	mkdir -p ASN1C
	pushd ASN1C
	asn1c -gen-PER ../../integer_array.asn1
	rm converter-sample.c
	popd
	gcc -o test -IASN1C ASN1C/*.c ../main.cc -g -D ARRAY_SIZE=$1 -D REPETITIONS=$2
	perf probe -d probe_test:encode -d probe_test:encode__return -d probe_test:decode -d probe_test:decode__return
	perf probe -x ./test encode=encode 
	perf probe -x ./test encode=encode%return
	perf probe -x ./test decode=decode
	perf probe -x ./test decode=decode%return
	perf record -e probe_test:encode -e probe_test:encode__return -e probe_test:decode -e probe_test:decode__return ./test
	perf archive
	popd
}

tests="256 512 1024 2048 4096"
for i in $tests ; do
	mtest $i 10000
done
