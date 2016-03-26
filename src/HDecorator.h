#pragma once

#include <string>
using namespace std;

class HDecorator {
public:
	string decorate(string& varName, string& base64String) {
		return "#pragma once\nconst char* " + varName + " = \"" + base64String + "\";\n";
	}
};
