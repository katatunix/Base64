#pragma once

#include <stdio.h>
#include <string.h>
#include "Buffer.h"

class Writer {
private:
	FILE* f;

public:
	Writer(const char* file) {
		f = fopen(file, "w");
	}

	~Writer() {
		if (f) fclose(f);
	}

	bool success() {
		return f != NULL;
	}

	void write(Buffer& buffer) {
		if (!success()) return;
		fwrite(buffer.ptr, 1, buffer.size, f);
	}

	void write(const char* str) {
		if (!success()) return;
		fputs(str, f);
	}
};
