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
	
	//-----------------------------------------------------------------------------
	//    Class:		DateTime
	//    method:		operator==(const Comparable& other) const
	//
	//    description:	true if the current object equal to other
	// 
	//    Parameters:	const Comparable &other  -- the other DateTime to compare
	//
	//    Called By:	main, >, <=
	//
	//	  Calls:		Date::operator==, CTime::operator==
	//
	//    Exceptions:	throws bad_cast if other is not a DateTime
	// 
	//    Returns:		true if the current object is before other;
	//				false otherwise
	//    History Log:
	//			4/22/17  NP  completed version 1.1
	// ----------------------------------------------------------------------------
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

	//-----------------------------------------------------------------------------
	//    Class:		DateTime
	//    method:		operator<(const Comparable& other) const
	//
	//    description:	true if the current object is before other
	// 
	//    Parameters:	const Comparable &other  -- the other DateTime to compare
	//
	//    Called By:	>, >=
	//
	//	  Calls:		Date::operator<, Date::operator==, CTime::operator<
	//
	//    Exceptions:	throws bad_cast if other is not a DateTime
	// 
	//    Returns:		true if the current object is before other;
	//				false otherwise
	//    History Log:
	//			4/22/17  NP  completed version 1.1
	// ----------------------------------------------------------------------------
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

	//-----------------------------------------------------------------------------
	//    Class:		DateTime
	//    method:		input(istream & sin)
	//
	//    description:	reads HH:MM:SS DD/MM/YYYY from istream and sets 
	//                  values in DateTime object
	// 
	//    Parameters:	istream & sin  -- the istream to read from
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	istream & operator >>
	// 
	//	  Calls:		Mutators of Date and CTime
	//
	//    Returns:      void
	//					
	//
	//    Exceptions:   
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
	//-----------------------------------------------------------------------------
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

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		print(ostream & sout) const
	//
	//    description:	prints pretty datetime to specified ostream
	// 
	//    Parameters:	ostream & sout  -- the ostream to print to
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	ostream & operator <<
	// 
	//	  Calls:		Accesors of Date
	//
	//    Returns:      void
	//					
	//
	//    Exceptions:   
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
	//-----------------------------------------------------------------------------
	void DateTime::print(ostream & sout) const
	{
		Date::print(sout);
		sout << ' ';
		CTime::print(sout);
	}

	//-----------------------------------------------------------------------------
	//    Class:		DateTime
	//    method:		ostream & operator << (ostream & sout, Date & date)
	//
	//    description:	invoke print and pass in sout into it
	// 
	//    Parameters:	ostream & sout -- ostream you'd like to print to
	//					DateTime & date -- date object you'd like to write to
	//
	//	  Programmers:  Norton Pengra
	//
	//    Called By:	main
	//
	//	  Calls:		DateTime::print
	// 
	//    Returns:      the ostream reference initially passed in
	//
	//    History Log:
	//			04/11/17  NP  appended to version 1.1
	//-----------------------------------------------------------------------------
	ostream & operator<<(ostream & sout, const DateTime & date)
	{
		date.print(sout);
		return sout;
	}

	//-----------------------------------------------------------------------------
	//    Class:		DateTime
	//    method:		istream & operator >> (istream & sin, Date & date)
	//
	//    description:	read from the specified input stream and write to date obj
	// 
	//    Parameters:	istream & sin -- istream you'd like to read from
	//					DateTime & date -- date object you'd like to write to
	//
	//	  Programmers:  Norton Pengra
	//
	//    Called By:	main
	//
	//	  Calls:		DateTime::input
	// 
	//    Returns:      the istream reference initially passed in
	//
	//    History Log:
	//			04/11/17  NP  appended to version 1.1
	//-----------------------------------------------------------------------------
	istream & operator>>(istream & sin, DateTime & date)
	{
		date.input(sin);
		return sin;
	}

}