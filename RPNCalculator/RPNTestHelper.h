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
