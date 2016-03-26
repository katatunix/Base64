#pragma once

#include <stdio.h>
#include <stdlib.h>

class Buffer {
public:
	char* ptr;
	int size;

	Buffer() : Buffer(NULL, 0) { }
	Buffer(char* _ptr, int _size) : ptr(_ptr), size(_size) { }

	void free() {
		if (ptr) {
			::free(ptr);
			ptr = NULL;
		}
	}

	bool nothing() {
		return !ptr || !size;
	}
};
