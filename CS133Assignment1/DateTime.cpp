//-----------------------------------------------------------------------------
//    File:             DateTime.cpp
//
//    Title:            DateTime Class
//
//    Description:	This file contains the class definition for DateTime
//
//    Programmer:	Paul Bladek & Norton Pengra
//   
//    Date:             4/24/2017
// 
//    Version:          1.0
//  
//    Environment:   Hardware: IBM Pentium  
//                   Software:  WinXP or later or .NET for execution;
//
//    Compiles under Microsoft C++ 2005
// 
//	  class DateTime:
//
//	  Virtual Non-inline:
//		virtual bool operator==(const Comparable &other)const;
//		virtual bool operator<(const Comparable &other)const;
//		virtual void input(istream& sin);
//		virtual void print(ostream& sout)const;
//
//    History Log:
//                      4/7/08  PB  completed version 1.0
// ----------------------------------------------------------------------------
#include "DateTime.h"

using namespace std;
namespace NP_DATETIME {
	
	bool DateTime::operator==(const Comparable &other) const {
		bool returnValue = false;
		try
		{
			bool dateEqual = Date::operator==(other);
			bool timeEqual = CTime::operator==(other);
			returnValue = dateEqual && timeEqual;
		}
		catch (bad_cast e)
		{
			// Should something happen here?
		}
		return returnValue;
	}

}