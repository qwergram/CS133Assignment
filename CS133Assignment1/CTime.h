//-----------------------------------------------------------------------------
//	File: CTime.h
//
//	class: CTime
//-----------------------------------------------------------------------------
#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <exception>
#include "Comparable.h"
using namespace std;

namespace NP_DATETIME
{
	
	const short MAXHOUR = 24;
    const short MAXMINSEC = 60;
//-----------------------------------------------------------------------------
//    Class:			CTime
//
//    File:             CTime.cpp
//
//    Title:            CTime Class
//
//    Description:		This file contains the class definition for CTime
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
//	  class Date:
//
//	  Properties:
//			int m_hour		-- 0 - 23
//			int m_minute	-- 0 - 59
//			int m_second	-- 0 - 59 
//
//	  Methods:
//			Inline:
//				short getHour()const    -- accessor for m_hour
//				short getMinute()const  -- accessor for m_minute  
//				short getSecond()const  -- accessor for m_second
//
//			Non-inline:
//					
//				virtual bool equals(const Comparable &other)const
//				virtual lessthan(const Comparable &other)const
//				virtual void input(istream& sin)
//				virtual void print(ostream& sout)const
//
//				void setHour(short hour)
//				void setMinute(short minute)
//				void setSecond(short second)
//				void print(ostream& sout)const
//
//    History Log:
//                      4/7/08  PB  completed version 1.0
// ----------------------------------------------------------------------------
	class CTime : virtual public Comparable
	{
	public:
		static const short HOURS_IN_DAY = 24;
		static const short SEXAGESIMAL_RATE = 60;

		CTime(void);
		CTime(int hour, int minute = 0, int second = 0);

		// pure virtuals that MUST be defined		
		virtual void input(istream& sin);
		virtual void print(ostream& sout)const;
		virtual bool operator==(const Comparable &other)const;
		virtual bool operator!=(const Comparable &other)const
			{return !((*this) == other);}
		virtual bool operator<(const Comparable &other)const;
		virtual bool operator>(const Comparable &other)const
			{return !((*this) < other) && !((*this) == other);}
		virtual bool operator<=(const Comparable &other)const
			{return !((*this) > other);}
		virtual bool operator>=(const Comparable &other)const
			{return !((*this) < other);}

		// Accessors
		short getHour()const { return m_hour; }
		short getMinute()const { return m_minute; }
		short getSecond()const { return m_second; }

		// Mutators
		void setHour(short hour);
		void setMinute(short minute);
		void setSecond(short second);

		void setCurrentTime(void);
		virtual ~CTime() {}

	protected:
		int m_hour;
		int m_minute;
		int m_second;
	};
	
	ostream& operator<<(ostream& sout, const CTime& time);
	istream& operator>>(istream& sin, CTime& time);
}