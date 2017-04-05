//-----------------------------------------------------------------------------
//	File: DayDriverNP.cpp
//-----------------------------------------------------------------------------

#include <iostream>
#include "main.h"
#include "CDay.h"

using namespace std;
using namespace NP_DAY;

//-----------------------------------------------------------------------------
//    function:			main()
//
//    description:		showcase of CDay abilities
// 
//	  returns:			0
//
//    Calls:            
//			CDay Constructor
//			CDay increment/decrement
//			CDay Addition/Subtraction
//
//    Called By:	
//			N/A
// 
//    Parameters:	
//			N/A
//
//    History Log:
//			4/4/16  NP  completed version 1.0
// ----------------------------------------------------------------------------
int main() {
	// Title
	cout << "NP_DAY Tests:" << endl << endl;
	
	// Build CDays
	cout << ">>> CDay day1" << endl;
	cout << ">>> CDay day2(SATURDAY)" << endl;
	CDay day1;
	CDay day2(SATURDAY);

	// Print CDay1
	cout << ">>> cout << day1 << endl;" << endl;
	cout << day1 << endl;
	cout << endl;

	// Print CDay2
	cout << ">>> cout << day2 << endl;" << endl;
	cout << day2 << endl;
	cout << endl;

	// CDay1 post/pre increment tests
	cout << ">>> cout ++day1;" << endl;
	cout << "... cout << " " << day1++;" << endl;
	cout << "... cout << " " << day1 << endl;" << endl;
	cout << ++day1;
	cout << " " << day1++;
	cout << " " << day1 << endl;
	cout << endl;

	// CDay2 post/pre increment tests
	cout << ">>> cout << ++day2;" << endl;
	cout << "... cout << " " << day2++;" << endl;
	cout << "... cout << " " << day2 << endl;" << endl;
	cout << ++day2;
	cout << " " << day2++;
	cout << " " << day2 << endl;
	cout << endl;

	// CDay1 post/pre decrement tests
	cout << ">>> cout << --day1;" << endl;
	cout << "... cout << " " << day1--;" << endl;
	cout << "... cout << " " << day1 << endl;" << endl;
	cout << --day1;
	cout << " " << day1--;
	cout << " " << day1 << endl;
	cout << endl;

	// CDay2 post/pre decrement tests
	cout << ">>> cout << --day2;" << endl;
	cout << "... cout << " " << day2--;" << endl;
	cout << "... cout << " " << day2 << endl;" << endl;
	cout << --day2;
	cout << " " << day2--;
	cout << " " << day2 << endl;
	cout << endl;

	// CDay1 input stream test
	cout << ">>> cout << \"enter a day: \"" << endl;
	cout << "... cin >> day1;" << endl;
	cout << endl;
	cout << "enter a day: ";
	cin >> day1;
	cout << endl;
	
	// print CDay1
	cout << ">>> cout << day1 << endl;" << endl;
	cout << day1 << endl;
	cout << endl;

	// CDay1 addition test
	cout << ">>> cout << day1 + 15 << endl;" << endl;
	cout << day1 + 15 << endl;
	cout << endl;

	// CDay1 subtraction test
	cout << ">>> cout << day1 - 15 << endl;" << endl;
	cout << day1 - 15 << endl;
	cout << endl;

	// Window Freeze
	string tmp;
	cout << ">>> Hit <enter> to return";
	getline(cin, tmp);
}