#include "catch.hpp"
#include "Base64Codec.h"
#include <string.h>
#include <string>
#include <vector>
using namespace std;

vector<char> charVec(const char* str) {
	int len = strlen(str);
	vector<char> v(len);
	memcpy(v.data(), str, len);
	return v;
}

TEST_CASE("Base64 encoding", "[base64_encoding]")
{
	Base64Codec codec;
	SECTION("The output should have = chars")
	{
		REQUIRE(codec.encode(charVec("nghia bui van")) == "bmdoaWEgYnVpIHZhbg==");
	}
	SECTION("The output should not have any = char")
	{
		REQUIRE(codec.encode(charVec("katatunix")) == "a2F0YXR1bml4");
	}
}

TEST_CASE("Base64 decoding", "[base64_decoding]")
{
	Base64Codec codec;
	SECTION("The input has = chars")
	{
		vector<char> output = codec.decode(string("bmdoaWEgYnVpIHZhbg=="));
		REQUIRE(string(output.data(), output.size()) == "nghia bui van");
	}
	SECTION("The input does not have any = char")
	{
		vector<char> output = codec.decode(string("a2F0YXR1bml4"));
		REQUIRE(string(output.data(), output.size()) == "katatunix");
	}
	SECTION("An exception should be thrown when the input length is not divided by 4")
	{
		REQUIRE_THROWS(codec.decode(string("12345")));
	}
}
