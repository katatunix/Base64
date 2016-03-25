#pragma once

#include "Writer.h"

class EndcodingWriter {
private:
	Writer& basicWriter;

public:
	EndcodingWriter(Writer& _basicWriter) : basicWriter(_basicWriter) { }

	bool write(const char* varName, const char* data) {
		if (!basicWriter.success()) return false;
		basicWriter.write("#pragma once\n");
		basicWriter.write("const char* ");
		basicWriter.write(varName);
		basicWriter.write(" = \"");
		basicWriter.write(data);
		basicWriter.write("\";\n");
		return true;
	}
};
