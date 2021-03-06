#pragma once

#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

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

	string encode(const vector<char>& input) {
		int input_len = input.size();
		int output_len = 4 * ((input_len + 2) / 3);
		char* output_data = (char*)malloc(output_len);

		const char* input_data = input.data();
		for (int i = 0, j = 0; i < input_len;) {
			unsigned int octet_a = i < input_len ? (unsigned char)input_data[i++] : 0;
			unsigned int octet_b = i < input_len ? (unsigned char)input_data[i++] : 0;
			unsigned int octet_c = i < input_len ? (unsigned char)input_data[i++] : 0;

			unsigned int triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

			output_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
			output_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
			output_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
			output_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
		}
		for (int i = 0; i < mod_table[input_len % 3]; i++) {
			output_data[output_len - 1 - i] = '=';
		}

		string ret(output_data, output_len);
		free(output_data);
		return ret;
	}

	vector<char> decode(string& input) {
		int input_len = input.length();
		if (input_len % 4 != 0) throw exception("Invalid Base64 string");

		const char* input_data = input.c_str();

		int output_len = input_len / 4 * 3;
		if (input_data[input_len - 1] == '=') --output_len;
		if (input_data[input_len - 2] == '=') --output_len;

		vector<char> output(output_len);
		char* output_data = output.data();

		for (int i = 0, j = 0; i < input_len;) {
			unsigned int sextet_a = input_data[i] == '=' ? 0 & i++ : decoding_table[input_data[i++]];
			unsigned int sextet_b = input_data[i] == '=' ? 0 & i++ : decoding_table[input_data[i++]];
			unsigned int sextet_c = input_data[i] == '=' ? 0 & i++ : decoding_table[input_data[i++]];
			unsigned int sextet_d = input_data[i] == '=' ? 0 & i++ : decoding_table[input_data[i++]];

			unsigned int triple = (sextet_a << 3 * 6)
				+ (sextet_b << 2 * 6)
				+ (sextet_c << 1 * 6)
				+ (sextet_d << 0 * 6);

			if (j < output_len) output_data[j++] = (triple >> 2 * 8) & 0xFF;
			if (j < output_len) output_data[j++] = (triple >> 1 * 8) & 0xFF;
			if (j < output_len) output_data[j++] = (triple >> 0 * 8) & 0xFF;
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
