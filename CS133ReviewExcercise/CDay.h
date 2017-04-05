//-----------------------------------------------------------------------------
//	File: CDay.h
//
//	class: CDay
//-----------------------------------------------------------------------------
#ifndef CDAY_H
#define CDAY_H

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

namespace NP_DAY
{
	
	//-----------------------------------------------------------------------------
	//    Enums:			dayTypes
	//
	//    Description:		Enum for each day type
	//
	//    Programmer:		Norton Pengra
	//   
	//    Date:             4/4/2017
	// 
	//    Version:          1.0
	//
	//-----------------------------------------------------------------------------
	enum dayType
	{
		NO_DAY,			// 0
		SUNDAY,			// 1	
		MONDAY,			// 2
		TUESDAY,		// 3
		WEDNESDAY,		// 4
		THURSDAY,		// 5
		FRIDAY,			// 6
		SATURDAY,		// 7
		OVERFLOW_DAY	// 8
	};

	//-----------------------------------------------------------------------------
	//    Class:			CDay
	//
	//    File:             CDay.cpp
	//
	//    Title:            CDay Class
	//
	//    Description:		This file contains the class definition for CDay
	//
	//    Programmer:		Norton Pengra
	//   
	//    Date:             4/4/2017
	// 
	//    Version:          1.0
	//  
	//    Environment:   Hardware:	Intel i7
	//                   Software:  Windows 10 Professional
	//
	//    Compiles under Microsoft C++ 2012
	// 
	//	  class CDay:
	//
	//		Properties:
	//			int mDay		-- 0 - 8 (dayType)
	//
	//		Methods:
	//			Inline:
	//				Constructor
	//				short getDay()const		// accessor for mDay
	//				void setDay()			// mutator for mDay
	//
	//			Non-inline:
	//					
	//				void print(ostream& sout) const;		// prints out as a day
	//				CDay next() const;                      // returns the next day
	//				CDay previous() const;					// returns the previous day
	//				CDay operator++();						// pre-increment
	//				CDay operator++(int);					// post-increment
	//				CDay operator--();						// pre-decrement
	//				CDay operator--(int);					// post-decrement
	//				CDay operator+(int d) const;			// addition of day and int
	//				CDay operator-(int d) const;			// subtraction of day and int
	//				operator dayType() const;				// cast operator to dayType
	//
	//    History Log:
	//			4/4/17  NP  completed version 1.0
	// ----------------------------------------------------------------------------

	class CDay // wrapper class for enum dayType
	{
	public:
		const static int DAYS_IN_WEEK = 7;
		CDay(dayType d = SUNDAY) : mDay(d) {}		// constructor
		dayType getDay() const { return mDay; }		// accessor for mDay
		void setDay(dayType d) { mDay = d; }		// mutator for mDay
		void print(ostream& sout) const;		// prints out as a day
		CDay next() const;                      // returns the next day
		CDay previous() const;					// returns the previous day
		CDay operator++();						// pre-increment
		CDay operator++(int);					// post-increment
		CDay operator--();						// pre-decrement
		CDay operator--(int);					// post-decrement
		CDay operator+(int d) const;			// addition of day and int
		CDay operator-(int d) const;			// subtraction of day and int
		operator dayType() const;				// cast operator to dayType
	private:
		dayType mDay;
	};

	ostream& operator << (ostream& sout, const CDay& d);	// insertion operator--prints out as a day
	istream& operator >> (istream& sin, CDay& d);			// extraction operator--should input a day name or number(0 - 8).

}  // end namespace NP_DAY 
#endif