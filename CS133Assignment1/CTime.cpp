//-----------------------------------------------------------------------------
//	File: CTime.cpp
//
//	class: CTime
//	methods:
//		void CTime::setCurrentTime()
//
//
//-----------------------------------------------------------------------------
#include "CTime.h"
namespace NP_DATETIME
{

	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		hour mutator
	//
	//    description:	sets hour to valid hour or 0
	// 
	//    Parameters:	short hour
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	
	// 
	//	  Calls:		
	//
	//    Returns:      
	//					
	//
	//    Exceptions:   
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
	//-----------------------------------------------------------------------------
	void CTime::setHour(short hour)
	{
		if (hour >= 0 && hour < HOURS_IN_DAY) {
			m_hour = hour;
		}
		else {
			m_hour = 0;
		}
	}

	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		minute mutator
	//
	//    description:	sets minute to valid minute or 0
	// 
	//    Parameters:	short minute
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	
	// 
	//	  Calls:		
	//
	//    Returns:      
	//					
	//
	//    Exceptions:   
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
	//-----------------------------------------------------------------------------
	void CTime::setMinute(short minute)
	{
		if (minute >= 0 && minute < SEXAGESIMAL_RATE) {
			m_minute = minute;
		}
		else {
			m_minute = 0;
		}
	}

	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		second mutator
	//
	//    description:	sets second to valid second or 0
	// 
	//    Parameters:	short second
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	
	// 
	//	  Calls:		
	//
	//    Returns:      
	//					
	//
	//    Exceptions:   
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
	//-----------------------------------------------------------------------------
	void CTime::setSecond(short second)
	{
		if (second >= 0 && second < SEXAGESIMAL_RATE) {
			m_second = second;
		}
		else {
			m_second = 0;
		}
	}

	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//	  method:		setCurrentTime()
	//
	//    description:	sets the time from the system clock
	//
	//    Called By:	constructor, mutators
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------
	void CTime::setCurrentTime()
	{
		time_t rawtime;
		tm *currentTimePtr;
		time(&rawtime);
		currentTimePtr = localtime(&rawtime);

		m_hour = currentTimePtr->tm_hour;
		m_minute = currentTimePtr->tm_min;
		m_second = currentTimePtr->tm_sec;
	}

	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		constructor
	//
	//    description:	builds time object from current time
	// 
	//    Parameters:	
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	
	// 
	//	  Calls:		Mutators of CTime
	//
	//    Returns:      
	//					
	//
	//    Exceptions:   
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
	//-----------------------------------------------------------------------------
	CTime::CTime(void)
	{
		this->setCurrentTime();
	}

	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		constructor
	//
	//    description:	builds time object from specified values
	// 
	//    Parameters:	int hour, int minute, int second
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	
	// 
	//	  Calls:		Mutators of CTime
	//
	//    Returns:      
	//					
	//
	//    Exceptions:   
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
	//-----------------------------------------------------------------------------
	CTime::CTime(int hour, int minute, int second)
	{
		this->setHour(hour);
		this->setMinute(minute);
		this->setSecond(second);
	}

	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		input(istream & sin)
	//
	//    description:	reads HH:MM:SS from istream and sets values in CTime object
	// 
	//    Parameters:	istream & sin  -- the istream to read from
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	istream & operator >>
	// 
	//	  Calls:		Mutators of CTime
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
	void CTime::input(istream & sin)
	{
		bool reset = false;
		short hour, minute, second;
		char c;

		sin >> hour;
		sin.get(c);
		if (c != ':') { reset = true; }

		sin >> minute;
		sin.get(c);
		if (c != ':') { reset = true; }

		sin >> second;

		if (reset) {
			hour = 0;
			minute = 0;
			second = 0;
		}
		else {
			if (hour < 0 || hour >= HOURS_IN_DAY)
				hour = 0;
			if (minute < 0 || minute >= SEXAGESIMAL_RATE)
				minute = 0;
			if (second < 0 || second >= SEXAGESIMAL_RATE)
				second = 0;
		}
		setHour(hour);
		setMinute(minute);
		setSecond(second);

	}

	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		print(ostream & sout) const
	//
	//    description:	prints text in HH:MM:SS to specified ostream
	// 
	//    Parameters:	ostream & sout  -- the ostream to print to
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	ostream & operator <<
	// 
	//	  Calls:		Accesors of CTime
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
	void CTime::print(ostream & sout) const
	{
		sout << getHour() << ':' << getMinute() << ':' << getSecond();
	}

	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		operator==(const Comparable& other) const
	//
	//    description:	true if the two objects are exactly the same
	// 
	//    Parameters:	const Comparable &other  -- the other Date to compare
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	main, >=, <=
	//
	//	  Calls:		Accesors of CTime
	// 
	//    Returns:      true if the two objects are exactly the same;
	//					false otherwise
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
	//-----------------------------------------------------------------------------
	bool CTime::operator==(const Comparable & other) const
	{
		bool returnValue = false;
		try
		{
			CTime otherTime = dynamic_cast<const CTime&>(other);
			returnValue = (
				m_hour == otherTime.getHour() &&
				m_minute == otherTime.getMinute() &&
				m_second == otherTime.getSecond()
				);
		}
		catch (bad_cast e)
		{
			// Should something happen here?
		}
		return returnValue;
	}

	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		operator < (const Comparable& other) const
	//
	//    description:	true if the two objects are exactly the same
	// 
	//    Parameters:	const Comparable &other  -- the other CTime to compare
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	main, >=, <=
	// 
	//	  Calls:		Accesors of CTime
	//
	//    Returns:      true if the the current object is less than the other.
	//					false otherwise
	//
	//    Exceptions:   Throws invalid_argument if other isn't CTime object
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
	//-----------------------------------------------------------------------------
	bool CTime::operator<(const Comparable & other) const
	{
		bool isLT = false;

		try {
			CTime otherTime = dynamic_cast<const CTime&>(other);

			bool hourIsLT = m_hour < otherTime.getHour();
			bool hourIsEq = m_hour == otherTime.getHour();
			bool minIsLT = m_minute < otherTime.getMinute();
			bool minIsEq = m_minute == otherTime.getMinute();
			bool secIsLT = m_second < otherTime.getSecond();

			if (hourIsLT)
				isLT = true;
			else if (hourIsEq && minIsLT)
				isLT = true;
			else if (hourIsEq && minIsEq && secIsLT)
				isLT = true;
		}
		catch (bad_cast e) {
			throw new invalid_argument("CTime can only be compared to CTime objects");
		}

		return isLT;
	}

	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		ostream & operator << (ostream & sout, const CTime & time)
	//
	//    description:	print the time to the specified ostream
	// 
	//    Parameters:	ostream & sout -- ostream you'd like to use
	//					const CTime & time -- time object to print
	//
	//	  Programmers:  Norton Pengra
	//
	//    Called By:	main
	//
	//	  Calls:		CTime::print()
	// 
	//    Returns:      the ostream reference initially passed in
	//
	//    History Log:
	//			04/11/17  NP  appended to version 1.1
	//-----------------------------------------------------------------------------
	ostream & operator << (ostream & sout, const CTime & time)
	{
		time.print(sout);
		return sout;
	}

	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		ostream & operator >> (istream & sin, CTime & time)
	//
	//    description:	read from the specified input stream and write to time obj
	// 
	//    Parameters:	istream & sin -- istream you'd like to read from
	//					CTime & time -- time object you'd like to write to
	//
	//	  Programmers:  Norton Pengra
	//
	//    Called By:	main
	//
	//	  Calls:		CTime::input
	// 
	//    Returns:      the istream reference initially passed in
	//
	//    History Log:
	//			04/11/17  NP  appended to version 1.1
	//-----------------------------------------------------------------------------
	istream & operator >> (istream & sin, CTime & time)
	{
		time.input(sin);
		return sin;
	}

}
