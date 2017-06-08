#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "avl.h"

TEST_CASE("A wonderful test", "[vector]") {
	std::vector<int> v(5);

	REQUIRE(v.size() == 5);
	REQUIRE(v.capacity() >= 5);

	SECTION("resizing bigger changes size and capacity") {
		v.resize(10);
		
		REQUIRE(v.size() == 10);
		REQUIRE(v.capacity() < 10);
	}
}