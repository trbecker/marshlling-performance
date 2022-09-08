#!/bin/bash

if [[ $UID != 0 ]] ; then
	echo "Needs to be run as root"
	exit -1
fi

mkdir -p $PWD/../../../results/asn1c-c-string
podman build -t asn1c-c-string .
podman run --privileged -it -v $PWD/../../../results/asn1c-c-string:/results:Z asn1c-c-string

if [ -n "$SUDO_UID" ] ; then
	echo "Fixing owner"
	chown -R $SUDO_UID $PWD/../../../results/asn1c-c-string
fi
