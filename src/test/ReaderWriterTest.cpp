#include "catch.hpp"
#include "Reader.h"
#include "Writer.h"
#include <string>
#include <vector>

using namespace std;

TEST_CASE("Reader and Writer", "[reader_writer]")
{
	SECTION("Together")
	{
		const char* file = "test.txt";
		const char* text = "nghia bui van";
		{
			Writer writer(file);
			writer.write(text);
		}
		Reader reader(file);
		vector<char> buffer = reader.read();
		REQUIRE(string(buffer.data(), buffer.size()) == text);
	}
	SECTION("Reading from an un-exsited file should throw exception")
	{
		Reader reader("no_file.txt");
		REQUIRE_THROWS(reader.read());
	}
	SECTION("Writing to an invalid file should throw exception")
	{
		Writer writer("\\\\invalid_file.txt");
		REQUIRE_THROWS(writer.write("test"));
	}
}
