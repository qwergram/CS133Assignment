#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "..\AVLTree\avl.h"

TEST_CASE("A wonderful test", "[vector]") {
	std::vector<int> v(5);

	REQUIRE(v.size() == 5);
	REQUIRE(v.capacity() >= 5);

	SECTION("resizing bigger changes size and capacity") {
		v.resize(10);
		
		REQUIRE(v.size() == 10);
		REQUIRE(v.capacity() < 10);
	}
	cin.get(); // keep window open
}