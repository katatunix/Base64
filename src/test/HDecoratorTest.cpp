#include "catch.hpp"
#include "HDecorator.h"
#include <string>
using namespace std;

TEST_CASE("Simple HDecorator", "[hdecorator]")
{
	HDecorator decorator;
	REQUIRE(decorator.decorate(string("theVar"), string("nghiabuivan"), 4) ==
		string("#pragma once\n") +
		"#include <string>\n" +
		"std::string theVar() {\n" +
		"return\n" +
		"std::string(\"nghi\") +\n" +
		"std::string(\"abui\") +\n" +
		"std::string(\"van\")\n" +
		";\n}\n"
	);
}
