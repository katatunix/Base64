#include <stdio.h>

#include "Buffer.h"
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
	Buffer input = reader.read();
	if (input.nothing()) {
		printf("error: could not read from input file\n");
		return 2;
	}

	Base64Codec codec;
	Buffer output = codec.encode(input);
	input.free();

	Writer basic(argv[2]);
	EndcodingWriter writer(basic);
	bool writeSuccess = writer.write(argv[3], output.ptr);
	output.free();

	if (!writeSuccess) {
		printf("error: could not write to output file\n");
	}

	return writeSuccess ? 0 : 3;
}
