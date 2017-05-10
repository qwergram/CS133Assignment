//-----------------------------------------------------------------------------
//	File: DateTime.h
//
//	class: DateTime
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
//	  Properties:
//		Date m_Date;  
//		CTime m_CTime;	
//
//	  Virtual Non-inline:
//		virtual bool operator==(const Comparable &other)const;
//		virtual bool operator<(const Comparable &other)const;
//		virtual void input(istream& sin);
//		virtual void print(ostream& sout)const;
//
//	  Virtual Inline:
//		virtual bool operator!=(const Comparable &other)const
//		virtual bool operator>(const Comparable &other)const
//		virtual bool operator<=(const Comparable &other)const
//		virtual bool operator>=(const Comparable &other)const
//
//    History Log:
//                      4/7/08  PB  completed version 1.0
// ----------------------------------------------------------------------------
#ifndef DATETIME_H
#define DATETIME_H
#include "Date.h"
#include "CTime.h"

using namespace std;
namespace NP_DATETIME {
	class DateTime : public Date, public CTime {
	public:
		// Constructors
		DateTime()
			: CTime(), Date() { }
		DateTime(short dayOfMonth, short month = 0, short year = LOWYEAR, 
				 short hour = 0, short minute = 0, short second = 0)
			: Date(dayOfMonth, month, year), CTime(hour, minute, second) { }
		DateTime(const Date & date, const CTime & time)
			: Date(date), CTime(time) { }

		// pure virtuals that MUST be defined
		virtual bool operator==(const Comparable &other)const;
		virtual bool operator!=(const Comparable &other)const
			{ return !((*this) == other); }
		virtual bool operator<(const Comparable &other)const;
		virtual bool operator>(const Comparable &other)const
			{ return !((*this) < other) && !((*this) == other); }
		virtual bool operator<=(const Comparable &other)const
			{ return !((*this) > other); }
		virtual bool operator>=(const Comparable &other)const
			{ return !((*this) < other); }
		
		virtual void input(istream& sin);
		virtual void print(ostream& sout)const;

	};

	ostream& operator<<(ostream& sout, const DateTime& date);
	istream& operator>>(istream& sin, DateTime& date);
}
#endif