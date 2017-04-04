//-----------------------------------------------------------------------------
//	File: Comparable.h
//
//	class: Comparable
//-----------------------------------------------------------------------------
#pragma once
#pragma warning(disable : 4996)
#include <iostream>
using namespace std;
//-----------------------------------------------------------------------------
//    Class:			Comparable
//
//    Title:            Comparable Class
//
//    Description:		This file contains the class definition for Comparable
//
//    Programmer:		Paul Bladek
//   
//    Date:             4/7/2008
// 
//    Version:          1.0
//  
//    Environment:   Hardware: IBM Pentium  
//                   Software:  WinXP or later or .NET for execution;
//
//    Compiles under Microsoft C++ 2005
// 
//	  class Comparable:
//			Abstract Base class  -- allows for comparison 
//	  Properties:
//		 none
//		 
//	  Methods:
//		pure virtuals:
//			virtual bool equals(const Comparable &other)const
//				returns true if both are identical; false otherwise
//			virtual lessthan(const Comparable &other)const
//				returns true if *this comes before other; false otherwise
//			virtual void input(istream& sin)
//				input: *this from sin
//			virtual void print(ostream& sout)const
//				output: *this to sout
//
//    History Log:
//                      4/7/08  PB  completed version 1.0
//-----------------------------------------------------------------------------

namespace PB_DATETIME
{
	class Comparable
	{
	public:
		virtual bool operator==(const Comparable &other)const = 0;
		virtual bool operator!=(const Comparable &other)const = 0;
		virtual bool operator<(const Comparable &other)const = 0;
		virtual bool operator>(const Comparable &other)const = 0;
		virtual bool operator<=(const Comparable &other)const = 0;
		virtual bool operator>=(const Comparable &other)const = 0;
		virtual void input(istream& sin) = 0;
		virtual void print(ostream& sout)const = 0;
		virtual ~Comparable() {}
	};
}