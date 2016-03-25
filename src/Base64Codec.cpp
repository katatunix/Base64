#include "Base64Codec.h"
#include <stdlib.h>

const char Base64Codec::encoding_table[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/'
};

const int Base64Codec::mod_table[] = { 0, 2, 1 };

Base64Codec::Base64Codec() {
	decoding_table = (char*)malloc(256);
	for (int i = 0; i < 64; i++) {
		decoding_table[(unsigned char) encoding_table[i]] = i;
	}
}

Base64Codec::~Base64Codec() {
	free(decoding_table);
}

char* Base64Codec::encode(const unsigned char* data, int input_length, int* output_length) {
	*output_length = 4 * ((input_length + 2) / 3);

	char* encoded_data = (char*)malloc(*output_length + 1);

	for (int i = 0, j = 0; i < input_length;) {
		unsigned int octet_a = i < input_length ? (unsigned char)data[i++] : 0;
		unsigned int octet_b = i < input_length ? (unsigned char)data[i++] : 0;
		unsigned int octet_c = i < input_length ? (unsigned char)data[i++] : 0;

		unsigned int triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

		encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
		encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
		encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
		encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
	}

	for (int i = 0; i < mod_table[input_length % 3]; i++) {
		encoded_data[*output_length - 1 - i] = '=';
	}

	encoded_data[*output_length] = 0;
	return encoded_data;
}

unsigned char* Base64Codec::decode(const char* data, int input_length, int* output_length) {
	if (input_length % 4 != 0) return NULL;

	*output_length = input_length / 4 * 3;
	if (data[input_length - 1] == '=') (*output_length)--;
	if (data[input_length - 2] == '=') (*output_length)--;

	unsigned char* decoded_data = (unsigned char*)malloc(*output_length);

	for (int i = 0, j = 0; i < input_length;) {
		unsigned int sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
		unsigned int sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
		unsigned int sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
		unsigned int sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

		unsigned int triple = (sextet_a << 3 * 6)
			+ (sextet_b << 2 * 6)
			+ (sextet_c << 1 * 6)
			+ (sextet_d << 0 * 6);

		if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
		if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
		if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
	}

	return decoded_data;
}
