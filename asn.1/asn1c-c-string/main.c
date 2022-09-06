#include "MyTypes.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#ifndef REPETITIONS
#define REPETITIONS 10000
#endif

#ifndef STR_SIZE
#define STR_SIZE 256
#endif

#define BUFFER_SIZE (STR_SIZE * 8 + 16 * 8)

// No escape, setting the string will require allocating the buffer.
asn_enc_rval_t encode(const char *str, void *encode_buffer, size_t buffer_size) {
	asn_enc_rval_t ret;
	MyTypes_t *myType = (MyTypes_t *)calloc(1, sizeof(MyTypes_t));

	OCTET_STRING_fromBuf(&myType->myString, str, STR_SIZE);
	ret = uper_encode_to_buffer(&asn_DEF_MyTypes, myType, encode_buffer, buffer_size);
	//xer_fprint(stdout, &asn_DEF_MyTypes, myType);

	SEQUENCE_free(&asn_DEF_MyTypes, myType, 0);

	return ret;
}

void decode(MyTypes_t *myType, void *encoded_buffer, size_t buffer_size) {
	uper_decode_complete(NULL, &asn_DEF_MyTypes, (void **)&myType,
		encoded_buffer, buffer_size);
}

int main(void) {
	char *str = (char *)malloc(STR_SIZE);
	assert(str);

	memset(str, 'a', STR_SIZE);

	for (int i = 0; i < REPETITIONS; i++) {
		asn_enc_rval_t rval;
		void *enc_buf = malloc(BUFFER_SIZE);

		rval = encode(str, enc_buf, BUFFER_SIZE);
		assert(rval.encoded > 0);

		MyTypes_t *myType = (MyTypes_t *)calloc(1, sizeof(MyTypes_t));
		decode(myType, enc_buf, rval.encoded);
		//xer_fprint(stdout, &asn_DEF_MyTypes, myType);

		SEQUENCE_free(&asn_DEF_MyTypes, myType, 0);
		free(enc_buf);
	}
}
