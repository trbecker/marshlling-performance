#include <stdio.h>	/* for stdout */
#include <stdlib.h>	/* for malloc() */
#include <assert.h>	/* for run-time control */
#include "MyTypes.h"	/* Include MyTypes definition */

int main(int argc, char *argv[]) {
	char buf[1024];	/* Hope, sufficiently large buffer */
	MyTypes_t *myType = 0;
	asn_dec_rval_t rval;
	char *filename;
	size_t size;
	FILE *f;

	/*
	 * Target variables.
	 */
	int *oid_array;	/* holds myObjectId */
	int oid_size;
	int *int_array;	/* holds mySeqOf */
	int int_size;
	int muxToken_set;	/* holds single bit */
	int modemToken_set;	/* holds single bit */

	/*
	 * Read in the input file.
	 */
	assert(argc == 2);
	filename = argv[1];
	f = fopen(filename, "r");
	assert(f);
	size = fread(buf, 1, sizeof buf, f);
	if(size == 0 || size == sizeof buf) {
		fprintf(stderr, "%s: Too large input\n", filename);
		exit(1);
	}

	/*
	 * Decode the XER buffer.
	 */
	rval = xer_decode(0, &asn_DEF_MyTypes, &myType, buf, size);
	assert(rval.code == RC_OK);

	/*
	 * Convert the OBJECT IDENTIFIER into oid_array/oid_size pair.
	 */
	/* Figure out the number of arcs inside OBJECT IDENTIFIER */
	oid_size = OBJECT_IDENTIFIER_get_arcs(&myType->myObjectId,
			0, sizeof(oid_array[0]), 0);
	assert(oid_size >= 0);
	/* Create the array of arcs and fill it in */
	oid_array = malloc(oid_size * sizeof(oid_array[0]));
	assert(oid_array);
	(void)OBJECT_IDENTIFIER_get_arcs(&myType->myObjectId,
			oid_array, sizeof(oid_array[0]), oid_size);

	/*
	 * Convert the sequence of integers into array of integers.
	 */
	int_size = myType->mySeqOf.list.count;
	int_array = malloc(int_size * sizeof(int_array[0]));
	assert(int_array);
	for(int_size = 0; int_size < myType->mySeqOf.list.count; int_size++)
		int_array[int_size] = *myType->mySeqOf.list.array[int_size];

	if(myType->myBitString.buf) {
		muxToken_set   = myType->myBitString.buf[0]
					& (1 << (7 - myBitString_muxToken));
		modemToken_set = myType->myBitString.buf[0]
					& (1 << (7 - myBitString_modemToken));
	} else {
		muxToken_set = modemToken_set = 0;	/* Nothing is set */
	}

	return 0;
}
