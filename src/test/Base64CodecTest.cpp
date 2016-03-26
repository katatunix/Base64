#include "catch.hpp"
#include "Base64Codec.h"
#include <string.h>
#include <string>
using namespace std;

TEST_CASE("Base64 encode", "[base64_encode]")
{
	Base64Codec codec;
	SECTION("Having = char")
	{
		char* input = "nghia bui van";
		Buffer buffer(input, strlen(input));
		REQUIRE(codec.encode(buffer) == "bmdoaWEgYnVpIHZhbg==");
	}
	SECTION("No having = char")
	{
		char* input = "katatunix";
		Buffer buffer(input, strlen(input));
		REQUIRE(codec.encode(buffer) == "a2F0YXR1bml4");
	}
}

TEST_CASE("Base64 decode", "[base64_decode]")
{
	Base64Codec codec;
	SECTION("Having = char")
	{
		string input("bmdoaWEgYnVpIHZhbg==");
		Buffer output = codec.decode(input);
		REQUIRE(string(output.data, output.len) == "nghia bui van");
		output.close();
	}
	SECTION("No having = char")
	{
		string input("a2F0YXR1bml4");
		Buffer output = codec.decode(input);
		REQUIRE(string(output.data, output.len) == "katatunix");
		output.close();
	}
}
