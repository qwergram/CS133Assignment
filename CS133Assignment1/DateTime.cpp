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
			const DateTime &otherDateTime =
				dynamic_cast<const DateTime&>(other);
			bool dateEqual = Date::operator==(otherDateTime);
			bool timeEqual = CTime::operator==(otherDateTime);
			returnValue = dateEqual && timeEqual;
		}
		catch (bad_cast e)
		{
			// Should something happen here?
		}
		return returnValue;
	}

	bool DateTime::operator<(const Comparable & other) const
	{
		bool returnValue = false;
		try 
		{
			const DateTime &otherDateTime = dynamic_cast<const DateTime&>(other);
			bool dateLT = Date::operator<(otherDateTime);
			bool dateEQ = Date::operator==(otherDateTime);
			bool timeLT = CTime::operator<(otherDateTime);
			returnValue = (dateLT || dateEQ && timeLT);
		}
		catch (bad_cast e) {
			// should something happen here?
		}
		return returnValue;
	}

	void DateTime::input(istream & sin)
	{
		
		Date::input(sin);
		char c;
		sin.get(c);
		if (c == ' ')
			CTime::input(sin);
		else {
			setHour(0);
			setMinute(0);
			setSecond(0);
		}

	}

	void DateTime::print(ostream & sout) const
	{
		Date::print(sout);
		sout << ' ';
		CTime::print(sout);
	}

	ostream & operator<<(ostream & sout, const DateTime & date)
	{
		date.print(sout);
		return sout;
	}

	istream & operator>>(istream & sin, DateTime & date)
	{
		date.input(sin);
		return sin;
	}

}