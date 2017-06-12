#include "RPNTestHelper.h"

inline string P4_RPNCALC::RPNTestHelper::getStackOutput(string input) {
	ostringstream ss;
	calc.depInj_setBuffer(input);
	while (!calc.getBuffer().empty())
		calc.depInj_runParse();
	ss << calc.getOutput();
	return ss.str();
}

inline string P4_RPNCALC::RPNTestHelper::getOutput(string input) {
	ostringstream ss;
	calc.depInj_setBuffer(input);
	while (!calc.getBuffer().empty())
		calc.depInj_runParse();
	ss << calc.depInj_lastOutput();
	return ss.str();
}
