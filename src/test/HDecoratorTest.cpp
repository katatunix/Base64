#include "catch.hpp"
#include "HDecorator.h"
#include <string>
using namespace std;

TEST_CASE("Simple HDecorator", "[hdecorator]")
{
	HDecorator decorator;
	REQUIRE(decorator.decorate(string("theVar"), string("abcd")) == "#pragma once\nconst char* theVar = \"abcd\";\n");
}
