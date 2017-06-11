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
		bool expectedOutput(string input, string output) {
			return getOutput(input) == output;
		}

		string getOutput(string input) {
			ostringstream ss;
			calc.setBuffer(input);
			while (!calc.getBuffer().empty())
				calc.runParse();
			ss << calc.lastOutput();
			return ss.str();
		}

		bool expectError(string input) {
			return expectedOutput(input, "<<error>>");
		}

		bool expectedOutput(int input, int output) {
			return expectedOutput(to_string(input), to_string(output));
		}
	private:
		CRPNCalc calc;
	};

}




#endif
