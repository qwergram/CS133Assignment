#include "RPNTestHelper.h"

//-----------------------------------------------------------------------------
// Title: RPNTestHelper
// Description: A helper class for running tests on RPNCalc class.
// Programmer: Tabitha Roemish, Cecilia Tong, Norton Pengra, Antonio Castelli -
//		see github link for individual contributions
//		
// Date: June 2017
// Version: 1.10
// Environment: 
//      Intel i7
//		Software: MS Windows 10 for execution;
//		Compiles under Microsoft Visual C++.Net 2015
// History Log:
//		https://github.com/qwergram/CS133Assignment/pull/7
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Title:		getStackOutput
// Description: returns the string representation of the first
//				item on the stack. Operation occurs after the
//				input operation.
// Called By:	testing units
// Calls:		calc dependency injection
// Parameters:	input command
// Returns:		string representation of last output from command
//				from the stack.
// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNTestHelper.cpp
// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
//--------------------------------------------------------------------
inline string P4_RPNCALC::RPNTestHelper::getStackOutput(string input) {
	ostringstream ss;
	calc.depInj_setBuffer(input);
	while (!calc.getBuffer().empty())
		calc.depInj_runParse();
	ss << calc.getOutput();
	return ss.str();
}

//--------------------------------------------------------------------
// Title:		getOutput
// Description: returns the string representation of the last
//				operation. Operation occurs after the
//				input operation.
// Called By:	testing units
// Calls:		calc dependency injection
// Parameters:	input command
// Returns:		string representation of last output from command
//				not from the stack.
// History Log: https://github.com/qwergram/CS133Assignment/blame/Tabitha/RPNCalculator/RPNTestHelper.cpp
// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
//--------------------------------------------------------------------
inline string P4_RPNCALC::RPNTestHelper::getOutput(string input) {
	ostringstream ss;
	calc.depInj_setBuffer(input);
	while (!calc.getBuffer().empty())
		calc.depInj_runParse();
	ss << calc.depInj_lastOutput();
	return ss.str();
}
