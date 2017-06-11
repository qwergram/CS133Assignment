//*
#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "RPNCalc.h"
#include "RPNTestHelper.h"

using namespace P4_RPNCALC;

TEST_CASE("Operation Methods")
{
	RPNTestHelper test;
	
	SECTION("Sanity Tests") {
		for (int n = 0; n < 100; n++) {
			REQUIRE(test.expectedOutput(n, n));
		}
	}

	SECTION("Method: clearAll()")
	{
		REQUIRE(test.expectedOutput("50", "50"));
		REQUIRE(test.expectedOutput("c", ""));
		REQUIRE(test.expectedOutput("50 100 +", "150"));
		REQUIRE(test.expectedOutput("c", ""));
		REQUIRE(test.expectedOutput("50 100 + 200", "200"));
		REQUIRE(test.expectedOutput("c", ""));
		REQUIRE(test.expectedOutput("50", "50"));
		REQUIRE(test.expectedOutput("C", ""));
		REQUIRE(test.expectedOutput("50 100 +", "150"));
		REQUIRE(test.expectedOutput("C", ""));
		REQUIRE(test.expectedOutput("50 100 + 200", "200"));
		REQUIRE(test.getOutput("C") == "");
	}
	
	/*
	SECTION("Method: clearEntry()")
	{
		REQUIRE(test.expectedInputOutput("50", "50"));
		REQUIRE(test.expectedInputOutput("ce", ""));
		REQUIRE(test.expectedInputOutput("50 100 +", "150"));
		REQUIRE(test.expectedInputOutput("ce", ""));
		REQUIRE(test.expectedInputOutput("50 100 + 200", "200"));
		REQUIRE(test.expectedInputOutput("ce", "150"));
		REQUIRE(test.expectedInputOutput("ce", ""));
		REQUIRE(test.expectedInputOutput("50", "50"));
		REQUIRE(test.expectedInputOutput("CE", ""));
		REQUIRE(test.expectedInputOutput("50 100 +", "150"));
		REQUIRE(test.expectedInputOutput("CE", ""));
		REQUIRE(test.expectedInputOutput("50 100 + 200", "200"));
		REQUIRE(test.expectedInputOutput("CE", "150"));
		REQUIRE(test.expectedInputOutput("CE", ""));
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
		REQUIRE(test.expectedInputOutput("3 +", "6"));
		REQUIRE(test.expectedInputOutput("10 100 +", "110"));
		REQUIRE(test.expectedInputOutput("10 100+", "110"));
		REQUIRE(test.expectedInputOutput("+", "<<error>>"));
	}
	
	SECTION("Method: combinations of add() & subtract()")
	{
		REQUIRE(test.expectedInputOutput("4.4 5.5 + 60 -", "-50.1"));
		REQUIRE(test.expectedInputOutput("4.4 5.5 - 60 +", "58.9"));
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
		REQUIRE(test.expectedInputOutput("10 100 -", "-90"));
		REQUIRE(test.expectedInputOutput("10 100-", "-90"));
		REQUIRE(test.expectedInputOutput("-", "<<error>>"));
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
		REQUIRE(test.expectedInputOutput("-2 *", "-48"));
		REQUIRE(test.expectedInputOutput("10 100 *", "1000"));
		REQUIRE(test.expectedInputOutput("10 100*", "1000"));
		REQUIRE(test.expectedInputOutput("5.5 2.2*", "12.1"));
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
		REQUIRE(test.expectedInputOutput("100 10 /", "10"));
		REQUIRE(test.expectedInputOutput("100 10/", "10"));
		REQUIRE(test.expectedInputOutput("/", "<<error>>"));
	}

	SECTION("Method: mod()") 
	{
		REQUIRE(test.expectedInputOutput("16 8 6 %", "2"));
		REQUIRE(test.expectedInputOutput("%", "0"));
		REQUIRE(test.expectedInputOutput("c", ""));
		REQUIRE(test.expectedInputOutput("%", "<<error>>"));
		REQUIRE(test.expectedInputOutput("10 1 %", "0"));
		REQUIRE(test.expectedInputOutput("10 2 %", "0"));
		REQUIRE(test.expectedInputOutput("10 3 %", "1"));
		REQUIRE(test.expectedInputOutput("10 4 %", "2"));
		REQUIRE(test.expectedInputOutput("10 5 %", "0"));
		REQUIRE(test.expectedInputOutput("10 6 %", "4"));
		REQUIRE(test.expectedInputOutput("10 7 %", "3"));
		REQUIRE(test.expectedInputOutput("10 8 %", "2"));
		REQUIRE(test.expectedInputOutput("10 9 %", "1"));
		REQUIRE(test.expectedInputOutput("10 10 %", "0"));
		REQUIRE(test.expectedInputOutput("100 70 %", "30"));
		REQUIRE(test.expectedInputOutput("100 70%", "30"));
	}

	SECTION("Method: exp()")
	{
		REQUIRE(test.expectedInputOutput("10 2 ^", "100"));
		REQUIRE(test.expectedInputOutput("10 2 2 ^", "4"));
		REQUIRE(test.expectedInputOutput("^", "10000"));
		REQUIRE(test.expectedInputOutput("-10 2 ^", "100"));
		REQUIRE(test.expectedInputOutput("-10 3 ^", "-1000"));
		REQUIRE(test.expectedInputOutput("-10 3^", "-1000"));
		REQUIRE(test.expectedInputOutput("0^", "1"));
		REQUIRE(test.expectedInputOutput("^", "<<error>>"));
		REQUIRE(test.expectedInputOutput("c", ""));
		REQUIRE(test.expectedInputOutput("100 100^", "1e+200"));
	}

	SECTION("Method: neg()")
	{
		REQUIRE(test.expectedInputOutput("-1000", "-1000"));
		REQUIRE(test.expectedInputOutput("M", "1000"));
		REQUIRE(test.expectedInputOutput("-1000 -1*", "1000"));
		REQUIRE(test.expectedInputOutput("M", "-1000"));
		REQUIRE(test.expectedInputOutput("-4/", "-250"));
		REQUIRE(test.expectedInputOutput("m", "250"));
		REQUIRE(test.expectedInputOutput("-2*", "-500"));
		REQUIRE(test.expectedInputOutput("m", "500"));
		REQUIRE(test.expectedInputOutput("c", ""));
		REQUIRE(test.expectedInputOutput("m", "<<error>>"));
		REQUIRE(test.expectedInputOutput("c", ""));
		REQUIRE(test.expectedInputOutput("M", "<<error>>"));
	}
	
	SECTION("Method: rotateDown()")
	{
		REQUIRE(test.expectedInputOutput("100 200", "200"));
		REQUIRE(test.expectedInputOutput("D", "100"));
		REQUIRE(test.expectedInputOutput("D", "200"));
		REQUIRE(test.expectedInputOutput("d", "100"));
		REQUIRE(test.expectedInputOutput("d", "200"));
		REQUIRE(test.expectedInputOutput("c", ""));
		REQUIRE(test.expectedInputOutput("D", "<<error>>"));
		REQUIRE(test.expectedInputOutput("c", ""));
		REQUIRE(test.expectedInputOutput("d", "<<error>>"));
	}
	
	SECTION("Method: rotateUp()")
	{
		REQUIRE(test.expectedInputOutput("300 500", "500"));
		REQUIRE(test.expectedInputOutput("U", "300"));
		REQUIRE(test.expectedInputOutput("U", "500"));
		REQUIRE(test.expectedInputOutput("u", "300"));
		REQUIRE(test.expectedInputOutput("u", "500"));
		REQUIRE(test.expectedInputOutput("c", ""));
		REQUIRE(test.expectedInputOutput("U", "<<error>>"));
		REQUIRE(test.expectedInputOutput("c", ""));
		REQUIRE(test.expectedInputOutput("u", "<<error>>"));
	}
	
	SECTION("Methods: saveToFile(), loadProgram(), recordProgram(), runProgram()")
	{
		REQUIRE(test.expectedInputOutput("R", "<<error>>"));
		REQUIRE(test.expectedInputOutput("F", "<<error>>"));
		REQUIRE(test.expectedInputOutput("p", "0>"));
		REQUIRE(test.expectedInputOutput("5 10 +", "1>"));
		REQUIRE(test.expectedInputOutput("20 30 -", "2>"));
		//REQUIRE(test.expectedInputOutput("P", ""));
		//REQUIRE(test.expectedInputOutput("f", "Enter a filename:"));
		REQUIRE(test.expectedInputOutput("test1", ""));
		//REQUIRE(test.expectedInputOutput("l", "Enter a filename:"));
		REQUIRE(test.expectedInputOutput("test", "error"));
		//REQUIRE(test.expectedInputOutput("L", "Enter a filename:"));
		REQUIRE(test.expectedInputOutput("test1", ""));
		REQUIRE(test.expectedInputOutput("r", "-10"));	
		REQUIRE(test.expectedInputOutput("c", ""));
	}
	
	SECTION("Methods: getReg(), setReg()")
	{
		REQUIRE(test.expectedInputOutput("s0", "<<error>>"));
		REQUIRE(test.expectedInputOutput("S1", "<<error>>"));
		REQUIRE(test.expectedInputOutput("s5", "<<error>>"));
		REQUIRE(test.expectedInputOutput("G0", "0"));
		REQUIRE(test.expectedInputOutput("g1", "0"));
		REQUIRE(test.expectedInputOutput("G5", "0"));
		REQUIRE(test.expectedInputOutput("1000", "1000"));
		REQUIRE(test.expectedInputOutput("s5", "1000"));
		REQUIRE(test.expectedInputOutput("2.5", "2.5"));
		REQUIRE(test.expectedInputOutput("S0", "2.5"));
		REQUIRE(test.expectedInputOutput("G5", "1000"));
		REQUIRE(test.expectedInputOutput("g0", "2.5"));
	}
	//*/
}
//*/