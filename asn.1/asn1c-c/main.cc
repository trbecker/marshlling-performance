#include <unistd.h>
#include "IntArray.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE 256
#endif

#ifndef REPETITIONS
#define REPETITIONS 10000
#endif

#define BUFFER_SIZE ((ARRAY_SIZE + 10) * sizeof(long))

void encode(IntArray_t *array, void *encode_buffer, size_t buffer_size, int *arr)
{
	uper_encode_to_buffer(&asn_DEF_IntArray, array, encode_buffer, buffer_size);
}

void decode(IntArray_t *array, void *buffer, size_t buffer_size)
{
	uper_decode_complete(NULL, &asn_DEF_IntArray, (void **)&array, buffer, buffer_size);
}

int main(void)
{
	int i = REPETITIONS;

	int *arr = (int *)calloc(ARRAY_SIZE, sizeof(int));
	for(int i = 0; i < ARRAY_SIZE; i++)
		arr[i] = i;

	while (i--) {
		IntArray_t *array = (IntArray_t *)calloc(1, sizeof(IntArray_t));
		void *encode_buffer = malloc(BUFFER_SIZE);

		for (int i = 0; i < ARRAY_SIZE; i++)
			ASN_SEQUENCE_ADD(array, &arr[i]);

		encode(array, encode_buffer, BUFFER_SIZE, arr);
		decode(array, encode_buffer, BUFFER_SIZE);

		free(array);
		free(encode_buffer);
		sleep(1);
	}
	free(arr);
}
