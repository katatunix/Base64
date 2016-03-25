#pragma once

class Base64Codec {
private:
	char* decoding_table;
	static const char encoding_table[];
	static const int mod_table[];

public:
	Base64Codec();
	~Base64Codec();

	char* encode(const unsigned char* data, int input_length, int* output_length);
	unsigned char* decode(const char* data, int input_length, int* output_length);
};
