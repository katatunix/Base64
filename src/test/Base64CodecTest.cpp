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

TEST_CASE("Base64 encoding", "[base64_encode]")
{
	Base64Codec codec;
	SECTION("Having '=' char")
	{
		REQUIRE(codec.encode(charVec("nghia bui van")) == "bmdoaWEgYnVpIHZhbg==");
	}
	SECTION("Not having '=' char")
	{
		REQUIRE(codec.encode(charVec("katatunix")) == "a2F0YXR1bml4");
	}
}

TEST_CASE("Base64 decoding", "[base64_decode]")
{
	Base64Codec codec;
	SECTION("Having '=' char")
	{
		vector<char> output = codec.decode(string("bmdoaWEgYnVpIHZhbg=="));
		REQUIRE(string(output.data(), output.size()) == "nghia bui van");
	}
	SECTION("Not having '=' char")
	{
		vector<char> output = codec.decode(string("a2F0YXR1bml4"));
		REQUIRE(string(output.data(), output.size()) == "katatunix");
	}
}
