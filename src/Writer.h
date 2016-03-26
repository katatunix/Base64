#pragma once

#include <stdio.h>
#include <string.h>
#include "Buffer.h"

using namespace std;

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

	bool write(Buffer& buffer) {
		if (!success()) return false;
		fwrite(buffer.data, 1, buffer.len, f);
		return true;
	}

	bool write(const string& str) {
		return write(str.c_str());
	}

	bool write(const char* str) {
		if (!success()) return false;
		fputs(str, f);
		return true;
	}
};
