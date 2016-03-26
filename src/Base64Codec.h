#pragma once

#include "Buffer.h"

class Base64Codec {
private:
	char* decoding_table;
	static const char encoding_table[];
	static const int mod_table[];

public:
	Base64Codec() {
		decoding_table = (char*)malloc(256);
		for (int i = 0; i < 64; i++) {
			decoding_table[(unsigned char) encoding_table[i]] = i;
		}
	}

	~Base64Codec() {
		free(decoding_table);
	}

	Buffer encode(Buffer& input) {
		Buffer output;
		output.size = 4 * ((input.size + 2) / 3);
		output.ptr = (char*)malloc(output.size + 1);

		char* data = input.ptr;
		for (int i = 0, j = 0; i < input.size;) {
			unsigned int octet_a = i < input.size ? (unsigned char)data[i++] : 0;
			unsigned int octet_b = i < input.size ? (unsigned char)data[i++] : 0;
			unsigned int octet_c = i < input.size ? (unsigned char)data[i++] : 0;

			unsigned int triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

			output.ptr[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
			output.ptr[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
			output.ptr[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
			output.ptr[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
		}

		for (int i = 0; i < mod_table[input.size % 3]; i++) {
			output.ptr[output.size - 1 - i] = '=';
		}

		output.ptr[output.size] = 0;
		return output;
	}

	Buffer decode(Buffer& input) {
		Buffer output;
		if (input.size % 4 != 0) return output;

		output.size = input.size / 4 * 3;
		if (input.ptr[input.size - 1] == '=') --output.size;
		if (input.ptr[input.size - 2] == '=') --output.size;

		output.ptr = (char*)malloc(output.size);

		char* data = input.ptr;
		for (int i = 0, j = 0; i < input.size;) {
			unsigned int sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
			unsigned int sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
			unsigned int sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
			unsigned int sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

			unsigned int triple = (sextet_a << 3 * 6)
				+ (sextet_b << 2 * 6)
				+ (sextet_c << 1 * 6)
				+ (sextet_d << 0 * 6);

			if (j < output.size) output.ptr[j++] = (triple >> 2 * 8) & 0xFF;
			if (j < output.size) output.ptr[j++] = (triple >> 1 * 8) & 0xFF;
			if (j < output.size) output.ptr[j++] = (triple >> 0 * 8) & 0xFF;
		}

		return output;
	}
};

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
