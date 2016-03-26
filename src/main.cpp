#include <string>
#include <exception>
#include <iostream>

#include "Buffer.h"
#include "Reader.h"
#include "Base64Codec.h"
#include "HDecorator.h"
#include "Writer.h"

using namespace std;

void usage() {
	cout << "Usage: Base64.exe input.bdae output.h g_variable\n";
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		usage();
		return 1;
	}

	try {
		Reader reader(argv[1]);
		Buffer input = reader.read();

		Base64Codec codec;
		string output = codec.encode(input);
		input.close();

		HDecorator decorator;
		string header = decorator.decorate(string(argv[3]), output);

		Writer writer(argv[2]);
		writer.write(header);

		return 0;
	} catch (exception& ex) {
		cout << string("Error: ") + ex.what() + "\n";
		return 1;
	}
}
