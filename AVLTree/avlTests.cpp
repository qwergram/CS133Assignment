#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "avl.h"

using namespace NP_AVL;

TEST_CASE("Testing inserting and balances", "[avl]") {
	auto item = avl<int>();
	
	SECTION("adding one item") {
		item.insert(1);
		REQUIRE(item.getHeight() == 1);
	}

	cin.get(); // keep window open
}