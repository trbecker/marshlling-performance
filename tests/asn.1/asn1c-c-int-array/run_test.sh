#!/bin/bash

if [[ $UID != 0 ]] ; then
	echo "Needs to be run as root"
	exit -1
fi

mkdir -p $PWD/../../../results/asn1c-c-int-array
podman build -t asn1c-c-int-array .
podman run --privileged -it -v $PWD/../../../results/asn1c-c-int-array:/results:Z asn1c-c-int-array
