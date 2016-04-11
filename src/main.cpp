#include <string>
#include <vector>
#include <exception>
#include <iostream>

#include "Reader.h"
#include "Base64Codec.h"
#include "HDecorator.h"
#include "Writer.h"

using namespace std;

void usage() {
	cout << "Usage: Base64.exe input.bdae output.h func_name max_length_of_each_part\n";
}

int main(int argc, char* argv[]) {
	if (argc != 5) {
		usage();
		return 1;
	}

	try {
		Reader reader(argv[1]);
		vector<char> input = reader.read();

		Base64Codec codec;
		string output = codec.encode(input);

		HDecorator decorator;
		string header = decorator.decorate(string(argv[3]), output, atoi(argv[4]));

		Writer writer(argv[2]);
		writer.write(header);

		return 0;
	} catch (exception& ex) {
		cout << "Error: " << ex.what() << "\n";
		return 1;
	}
}
