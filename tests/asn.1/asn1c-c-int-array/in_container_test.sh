#!/bin/bash

mkdir /tmp/stage

function do_test {
	cp test-$1 /tmp/stage/test
	mkdir -p /results/$1

	pushd /tmp/stage
	perf probe -d probe_test:encode -d probe_test:encode__return -d probe_test:decode -d probe_test:decode__return
        perf probe -x ./test encode=encode
        perf probe -x ./test encode=encode%return
        perf probe -x ./test decode=decode
        perf probe -x ./test decode=decode%return
	perf record -e probe_test:encode -e probe_test:encode__return -e probe_test:decode -e probe_test:decode__return ./test
	perf archive
	cp perf.data perf.data.tar.bz2 /results/$1
	popd
}

for i in 256 512 1024 2048 4096 ; do
	do_test $i 2>&1 >/dev/null
	echo "Completed $i"
done
