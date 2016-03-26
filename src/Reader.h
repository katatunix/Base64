#pragma once

#include <stdio.h>
#include <string>
#include <exception>
#include <vector>

using namespace std;

class Reader {
private:
	const char* file;

public:
	Reader(const char* _file) : file(_file) { }

	vector<char> read() {
		FILE* f = fopen(file, "r");
		if (!f) {
			throw exception((string("Could not open file \"") + file + "\"").c_str());
		}

		fseek(f, 0, SEEK_END);
		int len = ftell(f);
		vector<char> data(len);
		rewind(f);
		fread(data.data(), 1, len, f);
		fclose(f);

		return data;
	}
};
