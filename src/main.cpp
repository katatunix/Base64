#include <stdio.h>
#include <string>

#include "Buffer.h"
#include "Reader.h"
#include "Base64Codec.h"
#include "HDecorator.h"
#include "Writer.h"

using namespace std;

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
	string output = codec.encode(input);
	input.free();

	HDecorator decorator;
	string header = decorator.decorate(string(argv[3]), output);

	Writer writer(argv[2]);
	bool writeSuccess = writer.write(header);
	if (!writeSuccess) {
		printf("error: could not write to output file\n");
	}

	return writeSuccess ? 0 : 3;
}
