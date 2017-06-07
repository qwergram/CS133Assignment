#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "RPNCalc.h"
#include "RPNTestHelper.h"

using namespace PB_CALC;

TEST_CASE("Operation Methods")
{
	SECTION("Method: add Test")
	{
		RPNTestHelper test;

		REQUIRE(test.expectedInputOutput("3 5 +", "8"));
		
	}
}