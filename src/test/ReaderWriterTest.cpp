#include "catch.hpp"
#include "Reader.h"
#include "Writer.h"
#include <string>
using namespace std;

TEST_CASE("Reader and Writer", "[reader_writer]")
{
	SECTION("Together")
	{
		const char* file = "test.txt";
		{
			Writer writer(file);
			writer.write("nghia bui van");
		}
		Reader reader(file);
		Buffer buffer = reader.read();
		REQUIRE(string(buffer.data, buffer.len) == "nghia bui van");
	}
	SECTION("Reading an un-exsited file should throw exception")
	{
		Reader reader("no_file.txt");
		REQUIRE_THROWS(reader.read());
	}
	SECTION("Writing to invalid file should throw exception")
	{
		Writer writer("\\\\invalid_file.txt");
		REQUIRE_THROWS(writer.write("test"));
	}
}
