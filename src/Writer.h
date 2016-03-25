#pragma once

#include <stdio.h>
#include <string.h>

class Writer {
private:
	FILE* f;

public:
	Writer(const char* file) {
		f = fopen(file, "w");
	}

	~Writer() {
		if (success()) fclose(f);
	}

	bool success() {
		return f != NULL;
	}

	void write(const char* data, int size) {
		if (!success()) return;
		fwrite(data, 1, size, f);
	}

	void write(const char* str) {
		if (!success()) return;
		fputs(str, f);
	}
};
