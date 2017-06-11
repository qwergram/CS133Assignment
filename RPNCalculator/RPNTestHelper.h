//----------------------------------------------------------------------
// file: RPNTestHelper.h
//----------------------------------------------------------------------
#ifndef RPNTESTHELP_H
#define RPNTESTHELP_H
#include <string>
#include <sstream>
#include <iostream> 
#include "RPNCalc.h"

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
// Classes:
//		class RPNTestHelper:
//			 
//			Public Methods Inline:
//				bool expectedInputOutput(string input, string output) -
//					takes string input and output and returns true if 
//					output matches calculator output
//
//			PPrivate:
//				CRPNCalc calc;
//				
// History Log:
//		https://github.com/qwergram/CS133Assignment/pull/7
//--------------------------------------------------------------------
namespace P4_RPNCALC
{
	class RPNTestHelper
	{
	public:
		RPNTestHelper() : calc(false) {  };
		bool expectedInputOutput(string input, string output) {
			ostringstream ss; 
			calc.setBuffer(input);
			while (!calc.getBuffer().empty())
				calc.runParse();
			try
			{
				ss << calc.getOutput();
			}
			catch (invalid_argument & e)
			{
				if (input == "c")
					ss << ""; 
				else
					ss << "<<error>>";	
			}
			return ss.str() == output;
		}
	private:
		CRPNCalc calc;
	};

}




#endif
