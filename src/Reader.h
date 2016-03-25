#pragma once

#include <stdlib.h>

class Reader {
private:
	FILE* f;

public:
	Reader(const char* file) {
		f = fopen(file, "r");
	}

	~Reader() {
		if (success()) fclose(f);
	}

	bool success() {
		return f != NULL;
	}

	const char* read() {
		if (!success()) return NULL;

		int s = size();
		char* buffer = (char*)malloc(s);

		rewind(f);
		fread(buffer, 1, s, f);
		return buffer;
	}

	int size() {
		if (!success()) return 0;
		fseek(f, 0, SEEK_END);
		return ftell(f);
	}
};
