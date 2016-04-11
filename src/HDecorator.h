#pragma once

#include <string>
using namespace std;

class HDecorator {
public:
	string decorate(string& funcName, string& base64String, int maxLengthOfEachVar) {
		string output = "#pragma once\n";
		output += "#include <string>\n";
		const char* base64Ptr = base64String.c_str();
		int len = base64String.length();
		int start = 0;
		output += "std::string " + funcName + "() {\n";
		output += "return\n";
		while (start < len) {
			int end = start + maxLengthOfEachVar;
			if (end > len) end = len;
			output += "std::string(\"" + string(base64Ptr + start, end - start) + "\")";
			start = end;
			if (start < len) {
				output += " +";
			}
			output += "\n";
		}
		output += ";\n}\n";
		return output;
	}
};
