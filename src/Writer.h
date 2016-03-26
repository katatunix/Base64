#pragma once

#include <stdio.h>
#include <string>
#include <exception>
#include <vector>

using namespace std;

class Writer {
private:
	FILE* f;
	exception ex;

public:
	Writer(const char* file) {
		f = fopen(file, "w");
		ex = exception( (string("Could not write to file \"") + file + "\"").c_str() );
	}

	~Writer() {
		if (!failed()) fclose(f);
	}

	void write(const vector<char>& buffer) {
		if (failed()) throw ex;
		fwrite(buffer.data(), 1, buffer.size(), f);
	}

	void write(const string& str) {
		write(str.c_str());
	}

	void write(const char* str) {
		if (failed()) throw ex;
		fputs(str, f);
	}

private:
	bool failed() {
		return !f;
	}
};
