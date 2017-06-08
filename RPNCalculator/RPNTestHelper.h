#ifndef RPNTESTHELP_H
#define RPNTESTHELP_H
#include <string>
#include <sstream>
#include <iostream> 
#include "RPNCalc.h"


namespace P4_RPNCALC
{

	class RPNTestHelper
	{
	public:
		RPNTestHelper() { this->calc.run(); };
		bool expectedInputOutput(string input, string output) {
			istringstream convertString(input);
			this->calc.input(convertString);
			stringstream ss;
			ss << calc;
			return ss.str() == output;
		}
	private:
		CRPNCalc calc;
	};

}




#endif
