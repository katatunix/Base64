#pragma once

#include <stdlib.h>
#include "Buffer.h"

class Reader {
private:
	FILE* f;

public:
	Reader(const char* file) {
		f = fopen(file, "r");
	}

	~Reader() {
		if (f) fclose(f);
	}

	Buffer read() {
		if (!f) return Buffer();

		fseek(f, 0, SEEK_END);
		int size = ftell(f);
		char* data = (char*)malloc(size);

		rewind(f);
		fread(data, 1, size, f);
		return Buffer(data, size);
	}
};
