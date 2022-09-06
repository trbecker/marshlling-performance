#include <unistd.h>
#include <stdio.h>
#include "IntArray.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE 256
#endif

#ifndef REPETITIONS
#define REPETITIONS 10000
#endif

#define BUFFER_SIZE ((ARRAY_SIZE + 10) * sizeof(long))

asn_enc_rval_t encode(IntArray_t *array, void *encode_buffer, size_t buffer_size)
{
	return uper_encode_to_buffer(&asn_DEF_IntArray, array, encode_buffer, buffer_size);
}

void decode(IntArray_t *array, void *buffer, size_t buffer_size)
{
	uper_decode_complete(NULL, &asn_DEF_IntArray, (void **)&array, buffer, buffer_size);
}

void cycle(int *inarray)
{
	asn_enc_rval_t enc_rval;
	IntArray *asnarray = (IntArray_t *)calloc(1, sizeof(IntArray_t));
	assert(asnarray);

	void *encode_buffer = malloc(BUFFER_SIZE);
	assert(encode_buffer);

	for (int i = 0; i < ARRAY_SIZE; i++)
		ASN_SEQUENCE_ADD(asnarray, &inarray[i]);

	enc_rval = encode(asnarray, encode_buffer, BUFFER_SIZE);
	if (enc_rval.encoded < 0) {
		printf("Failed to encode %s\n", enc_rval.failed_type->name);
		exit(-1);
	}

	free(asnarray);
	asnarray = (IntArray_t *)calloc(1, sizeof(IntArray_t));
	assert(asnarray);

	decode(asnarray, encode_buffer, BUFFER_SIZE);

	free(encode_buffer);
	free(asnarray);
}

int main(void)
{
	int *arr = (int *)calloc(ARRAY_SIZE, sizeof(int));
	assert(arr);

	for(int i = 0; i < ARRAY_SIZE; i++)
		arr[i] = i;

	for (int i = 0; i < REPETITIONS; i++)
		cycle(arr);

	free(arr);
}
