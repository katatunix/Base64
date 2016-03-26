#pragma once

#include <stdlib.h>
#include "Buffer.h"
#include <exception>

using namespace std;

class Reader {
private:
	const char* file;

public:
	Reader(const char* _file) : file(_file) { }

	Buffer read() {
		FILE* f = fopen(file, "r");
		if (!f) {
			throw exception((string("Could not open file ") + file).c_str());
		}

		fseek(f, 0, SEEK_END);
		int len = ftell(f);
		char* data = (char*)malloc(len);
		rewind(f);
		fread(data, 1, len, f);
		fclose(f);

		return Buffer(data, len);
	}
};
