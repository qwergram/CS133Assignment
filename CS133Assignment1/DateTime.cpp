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

	DateTime::DateTime() {
		m_time = CTime();
		m_date = Date();
	}

	DateTime::DateTime(short dayOfMonth, short month, short year, short hour, short minute, short second)
	{
		m_date = Date(dayOfMonth, month, year);
		m_time = CTime(hour, minute, second);
	}

}