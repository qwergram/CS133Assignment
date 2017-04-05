//-----------------------------------------------------------------------------
//	File: CDay.cpp
//-----------------------------------------------------------------------------

#include "CDay.h"

using namespace std;

namespace NP_DAY {

	//-----------------------------------------------------------------------------
	//    Class:			CDay
	//    method:			void CDay::print(ostream & sout) const
	//
	//    description:		sends string representation of current objet to 
	//						output stream.
	// 
	//    Calls:            
	//			N/A
	//
	//    Called By:	
	//			ostream& operator << (ostream& sout, const CDay& d);
	// 
	//    Parameters:	
	//			ostream & sout -- output stream
	//
	//    History Log:
	//			4/4/16  NP  completed version 1.0
	// ----------------------------------------------------------------------------
	void CDay::print(ostream & sout) const
	{
		switch (mDay)
		{
		case NP_DAY::SUNDAY:
			sout << "Sunday";
			break;
		case NP_DAY::MONDAY:
			sout << "Monday";
			break;
		case NP_DAY::TUESDAY:
			sout << "Tuesday";
			break;
		case NP_DAY::WEDNESDAY:
			sout << "Wednesday";
			break;
		case NP_DAY::THURSDAY:
			sout << "Thursday";
			break;
		case NP_DAY::FRIDAY:
			sout << "Friday";
			break;
		case NP_DAY::SATURDAY:
			sout << "Saturday";
			break;
		default:
			sout << "Not a day";
			break;
		}
	}

	//-----------------------------------------------------------------------------
	//    Class:			CDay
	//    method:			CDay CDay::next() const
	//
	//    description:		returns next day of week.
	// 
	//	  returns: CDay of next day
	//
	//    Calls:            
	//			CDay constructor
	//
	//    Called By:	
	//			CDay operator++();
	//			CDay operator++(int);
	// 
	//    Parameters:	
	//			N/A
	//
	//    History Log:
	//			4/4/16  NP  completed version 1.0
	// ----------------------------------------------------------------------------
	CDay CDay::next() const
	{
		// Sunday - Friday
		if (mDay >= SUNDAY && mDay <= FRIDAY) {
			return CDay(static_cast<dayType>(mDay + 1));
		}
		// Saturday (Wrap around)
		else if (mDay == SATURDAY)  {
			return CDay(SUNDAY);
		}
		// NO_DAY or OVERFLOW_DAY
		else {
			return CDay(mDay);
		}
	}

	//-----------------------------------------------------------------------------
	//    Class:			CDay
	//    method:			CDay CDay::previous() const
	//
	//    description:		returns previous day of week.
	// 
	//	  returns: CDay of previous day
	//
	//    Calls:            
	//			CDay constructor
	//
	//    Called By:	
	//			CDay operator--();
	//			CDay operator--(int);
	// 
	//    Parameters:	
	//			N/A
	//
	//    History Log:
	//			4/4/16  NP  completed version 1.0
	// ----------------------------------------------------------------------------
	CDay CDay::previous() const
	{
		// Monday - Saturday
		if (mDay >= MONDAY && mDay <= SATURDAY) {
			return CDay(static_cast<dayType>(mDay - 1));
		}
		// Sunday
		else if (mDay == SUNDAY) {
			return CDay(SATURDAY);
		}
		// NO_DAY or OVERFLOW_DAY
		else {
			return CDay(mDay);
		}
	}

	//-----------------------------------------------------------------------------
	//    Class:			CDay
	//    method:			CDay CDay::operator++()
	//
	//    description:		pre-increment the day
	// 
	//	  returns:			CDay of next day
	//
	//    Calls:            
	//			CDay CDay::next() const
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
	CDay CDay::operator++()
	{
		*this = next();
		return *this;
	}

	//-----------------------------------------------------------------------------
	//    Class:			CDay
	//    method:			CDay CDay::operator++(int)
	//
	//    description:		post-increment the day
	// 
	//	  returns:			CDay of next day
	//
	//    Calls:            
	//			CDay CDay::next() const
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
	CDay CDay::operator++(int)
	{
		CDay tmp = *this;
		*this = next();
		return tmp;
	}

	//-----------------------------------------------------------------------------
	//    Class:			CDay
	//    method:			CDay CDay::operator--()
	//
	//    description:		pre-decrement the day
	// 
	//	  returns:			CDay of previous day
	//
	//    Calls:            
	//			CDay CDay::previous() const
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
	CDay CDay::operator--()
	{
		*this = previous();
		return *this;
	}

	//-----------------------------------------------------------------------------
	//    Class:			CDay
	//    method:			CDay CDay::operator--(int)
	//
	//    description:		post-decrement the day
	// 
	//	  returns:			CDay of previous day
	//
	//    Calls:            
	//			CDay CDay::previous() const
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
	CDay CDay::operator--(int)
	{
		CDay tmp = *this;
		*this = previous();
		return tmp;
	}

	//-----------------------------------------------------------------------------
	//    Class:			CDay
	//    method:			CDay CDay::operator+(int d)
	//
	//    description:		addition override with integer
	// 
	//	  returns:			CDay with d days added.
	//
	//    Calls:            
	//			CDay Constructor
	//
	//    Called By:	
	//			CDay CDay::operator-(int d) const
	// 
	//    Parameters:	
	//			integer d
	//
	//    History Log:
	//			4/4/16  NP  completed version 1.0
	// ----------------------------------------------------------------------------
	CDay CDay::operator+(int d) const
	{
		if (mDay == NO_DAY || mDay == OVERFLOW_DAY) {
			return CDay(mDay);
		}

		int dayIndex = (static_cast<short>(mDay) + (d % 7));

		if (dayIndex > 0) {
			return CDay(dayType(dayIndex % 7));
		} 
		else if (dayIndex == 0) {
			return CDay(mDay);
		}
		
	}

	//-----------------------------------------------------------------------------
	//    Class:			CDay
	//    method:			CDay CDay::operator-(int d)
	//
	//    description:		subtraction override with integer
	// 
	//	  returns:			CDay with d days removed.
	//
	//    Calls:            
	//			CDay CDay::operator+(int d) const
	//
	//    Called By:	
	//			N/A
	// 
	//    Parameters:	
	//			integer d
	//
	//    History Log:
	//			4/4/16  NP  completed version 1.0
	// ----------------------------------------------------------------------------
	CDay CDay::operator-(int d) const
	{
		return *this + -d;
	}

	//-----------------------------------------------------------------------------
	//    Class:			CDay
	//    method:			CDay::operator dayType() const
	//
	//    description:		cast dayType overloader
	// 
	//	  returns:			dayType of class.
	//
	//    Calls:            
	//			N/A
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
	CDay::operator dayType() const
	{
		return mDay;
	}

	//-----------------------------------------------------------------------------
	//    function:			ostream & operator<<(ostream & sout, const CDay & d)
	//
	//    description:		output stream overload for CDay
	// 
	//	  returns:			outputstream
	//
	//    Calls:            
	//			void CDay::print(ostream & sout) const
	//
	//    Called By:	
	//			N/A
	// 
	//    Parameters:	
	//			ostream & sout -- output stream to print to
	//			const CDay & d -- CDay data to print
	//
	//    History Log:
	//			4/4/16  NP  completed version 1.0
	// ----------------------------------------------------------------------------
	ostream & operator<<(ostream & sout, const CDay & d)
	{
		d.print(sout);
		return sout;
	}

	//-----------------------------------------------------------------------------
	//    function:			istream & operator >> (istream & sin, CDay & d)
	//
	//    description:		input stream overload for CDay
	// 
	//	  returns:			inputstream
	//
	//    Calls:            
	//			void setDay(dayType d)
	//
	//    Called By:	
	//			N/A
	// 
	//    Parameters:	
	//			ostream & sin  -- intput stream to read from
	//			const CDay & d -- CDay data to set
	//
	//    History Log:
	//			4/4/16  NP  completed version 1.0
	// ----------------------------------------------------------------------------
	istream & operator >> (istream & sin, CDay & d)
	{
		string result;
		sin >> result;

		if (result == "0" || result == "No day") {
			d.setDay(NO_DAY);
		} 
		else if (result == "1" || result == "Sunday") {
			d.setDay(SUNDAY);
		} 
		else if (result == "2" || result == "Monday") {
			d.setDay(MONDAY);
		}
		else if (result == "3" || result == "Tuesday") {
			d.setDay(TUESDAY);
		}
		else if (result == "4" || result == "Wednesday") {
			d.setDay(WEDNESDAY);
		}
		else if (result == "5" || result == "Thursday") {
			d.setDay(THURSDAY);
		}
		else if (result == "6" || result == "Friday") {
			d.setDay(FRIDAY);
		}
		else if (result == "7" || result == "Saturday") {
			d.setDay(SATURDAY);
		} 
		else if (result == "8" || result == "Overflow day") {
			d.setDay(OVERFLOW_DAY);
		}
		else {
			sin.clear(ios::failbit);
		}
		
		return sin;
	}
}