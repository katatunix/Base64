#include <stdio.h>

#include "Reader.h"
#include "Base64Codec.h"
#include "Writer.h"
#include "EncodingWriter.h"

void usage() {
	printf("Usage: Base64.exe input.bdae output.h g_variable\n");
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		usage();
		return 1;
	}

	Reader reader(argv[1]);
	if (!reader.success()) {
		printf("error: could not read from input file\n");
		return 2;
	}
	unsigned char* inputData = (unsigned char*)reader.read();
	const int inputLen = reader.size();

	Base64Codec codec;
	int outputLen = 0;
	char* outputData = codec.encode(inputData, inputLen, &outputLen);
	free(inputData);

	Writer basic(argv[2]);
	EndcodingWriter writer(basic);
	int ret = 0;
	if (!writer.write(argv[3], outputData)) {
		printf("error: could not write to output file\n");
		ret = 3;
	}
	free(outputData);

	return ret;
}
