#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "RPNCalc.h"
#include "RPNTestHelper.h"

using namespace P4_RPNCALC;

TEST_CASE("Operation Methods")
{
	RPNTestHelper test;
	
	SECTION("Method: clearAll()")
	{
		REQUIRE(test.expectedInputOutput("50", "50"));
		REQUIRE(test.expectedInputOutput("c", ""));
		REQUIRE(test.expectedInputOutput("50 100 +", "150"));
		REQUIRE(test.expectedInputOutput("c", ""));
		REQUIRE(test.expectedInputOutput("50", "50"));
		REQUIRE(test.expectedInputOutput("C", ""));
		REQUIRE(test.expectedInputOutput("50 100 +", "150"));
		REQUIRE(test.expectedInputOutput("C", ""));
	}

	SECTION("Method: add()")
	{
		REQUIRE(test.expectedInputOutput("3 5 +", "8"));
		REQUIRE(test.expectedInputOutput("2 4 3 +", "7"));
		REQUIRE(test.expectedInputOutput("c", ""));
		REQUIRE(test.expectedInputOutput("3 4 + 6", "6"));
		REQUIRE(test.expectedInputOutput("4 +", "10"));
		REQUIRE(test.expectedInputOutput("-12 +", "-2"));
		REQUIRE(test.expectedInputOutput("5 +", "3"));
		REQUIRE(test.expectedInputOutput("3 +", "10"));	
	}
	
	SECTION("Method: add() & subtract()")
	{
		REQUIRE(test.expectedInputOutput("40 50 + 60 -", "30"));
		REQUIRE(test.expectedInputOutput("40 50 - 60 +", "50"));
		REQUIRE(test.expectedInputOutput("40 50 60 + -", "-70"));
		REQUIRE(test.expectedInputOutput("40 50 60 - +", "30"));
		REQUIRE(test.expectedInputOutput("-40 -50 + 60 -", "-150"));
		REQUIRE(test.expectedInputOutput("-40 -50 + -60 -", "-30"));
		REQUIRE(test.expectedInputOutput("-40 -50 - 60 +", "70"));
		REQUIRE(test.expectedInputOutput("-40 -50 - -60 +", "-50"));	
	}
	

	SECTION("Method: subtract()")
	{
		REQUIRE(test.expectedInputOutput("5 6 -", "-1"));
		REQUIRE(test.expectedInputOutput("3 9 4 -", "5"));
		REQUIRE(test.expectedInputOutput("-", "-2"));
		REQUIRE(test.expectedInputOutput("c", ""));
		REQUIRE(test.expectedInputOutput("-1 5 -", "-6"));
	}

	SECTION("Method: multiply()")
	{
		REQUIRE(test.expectedInputOutput("3 9 7 2 4 *", "8"));
		REQUIRE(test.expectedInputOutput("*", "56"));
		REQUIRE(test.expectedInputOutput("*", "504"));
		REQUIRE(test.expectedInputOutput("*", "1512"));
		REQUIRE(test.expectedInputOutput("*", "<<error>>"));
		REQUIRE(test.expectedInputOutput("c", ""));
		REQUIRE(test.expectedInputOutput("-4 -6 *", "24"));
		REQUIRE(test.expectedInputOutput("-2 *", "48"));
	}

	SECTION("Method: divide()")
	{
		REQUIRE(test.expectedInputOutput("16 4 2 /", "2"));
		REQUIRE(test.expectedInputOutput("/", "8"));
		REQUIRE(test.expectedInputOutput("c", ""));
		REQUIRE(test.expectedInputOutput("2 5 /", "0.4"));
		REQUIRE(test.expectedInputOutput("9 3 7 /", "0.428571"));
		REQUIRE(test.expectedInputOutput("-1 /", "-0.428571"));
		REQUIRE(test.expectedInputOutput("-1 / ", "0.428571"));
	}

	SECTION("Method: mod()") 
	{
		REQUIRE(test.expectedInputOutput("16 8 6 %", "2"));
		REQUIRE(test.expectedInputOutput("%", "0"));
		REQUIRE(test.expectedInputOutput("c", ""));

		REQUIRE(test.expectedInputOutput("", ""));
		REQUIRE(test.expectedInputOutput("", ""));
		REQUIRE(test.expectedInputOutput("", ""));
		
	}

	SECTION("Method: exp()")
	{
		REQUIRE(test.expectedInputOutput("", ""));
		REQUIRE(test.expectedInputOutput("", ""));
		REQUIRE(test.expectedInputOutput("", ""));
		REQUIRE(test.expectedInputOutput("", ""));
		REQUIRE(test.expectedInputOutput("", ""));
	}

	SECTION("Method: neg()")
	{
		REQUIRE(test.expectedInputOutput("", ""));
		REQUIRE(test.expectedInputOutput("", ""));
		REQUIRE(test.expectedInputOutput("", ""));
		REQUIRE(test.expectedInputOutput("", ""));
		REQUIRE(test.expectedInputOutput("", ""));
	}
}
