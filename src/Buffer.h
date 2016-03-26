#pragma once

#include <stdio.h>
#include <stdlib.h>

class Buffer {
public:
	char* data;
	int len;

	Buffer() : Buffer(NULL, 0) { }
	Buffer(char* _data, int _len) : data(_data), len(_len) { }

	void free() {
		if (data) {
			::free(data);
			data = NULL;
		}
	}

	bool nothing() {
		return !data;
	}
};
