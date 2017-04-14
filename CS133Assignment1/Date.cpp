//-----------------------------------------------------------------------------
//	File: Date.cpp
//
//	class: Date
//	methods:
//		Date::Date(short day, short month, short year)
//		bool Date::operator==(const Comparable &other)const
//		bool Date::operator<(const Comparable &other)const
//		void Date::setCurrentDate(void)
//		void Date::setDayOfWeek(void)
//		void Date::setDayOfYear(void)
//		short Date::countLeaps(short year)const
//		void Date::setDayOfMonth(short dayOfMonth)
//		void Date::setMonth(short month)
//		void Date::setYear(short year)
//-----------------------------------------------------------------------------
#include "Date.h"

namespace NP_DATETIME
{
	//-----------------------------------------------------------------------------
	//    method:		Date(short day, short month, short year) -- constructor
	//
	//    description:	creates a new Date object
	// 
	//    Calls:            setCurrentDate()
	//			daysInMonth(month, year)
	//			setDayOfYear()
	//			setDayOfWeek()
	// 
	//    Called By:	ostream& operator<<(ostream& sout, const CComplex &c)
	// 
	//    Parameters:	short day -- day to set
	//			short month -- month to set
	//			short year -- month to set
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------
	Date::Date(short day, short month, short year)
	{
		setDayOfMonth(day);
		setMonth(month - 1);
		setYear(year);
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		operator==(const Comparable& other) const
	//
	//    description:	true if the two objects are exactly the same
	// 
	//    Parameters:	const Comparable &other  -- the other Date to compare
	//
	//    Called By:	main, >=, <=
	// 
	//    Returns:          true if the two objects are exactly the same;
	//				false otherwise
	//    History Log:
	//			5/8/16  PB  completed version 1.1
	//-----------------------------------------------------------------------------
	bool Date::operator==(const Comparable &other) const
	{
		bool returnValue = false;
		try
		{
			const Date &otherDate =
				dynamic_cast<const Date&>(other);
			returnValue = (
				m_year == otherDate.m_year && 
				getDayOfYear() == otherDate.getDayOfYear()
				);
		}
		catch (bad_cast e)
		{
			// Should something happen here?
		}
		return returnValue;
	}
	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		operator<(const Comparable& other) const
	//
	//    description:	true if the current object is before other
	// 
	//    Parameters:	const Comparable &other  -- the other Date to compare
	//
	//    Called By:	main, >, <=
	//
	//	  Calls:		getYear, getDayOfYear
	//
	//    Exceptions:	throws bad_cast if other is not a Date
	// 
	//    Returns:		true if the current object is before other;
	//				false otherwise
	//    History Log:
	//			5/8/16  PB  completed version 1.1
	// ----------------------------------------------------------------------------

	bool Date::operator<(const Comparable &other) const
	{
		bool returnValue = false;
	
		try {
			Date otherDate = dynamic_cast<const Date&>(other);
			
			bool yearLT = otherDate.getYear() < getYear();
			bool yearEQ = otherDate.getYear() == getYear();
			bool dayLT = otherDate.getDayOfYear() < getDayOfYear();

			returnValue = (yearLT || yearEQ && dayLT);
		}
		catch (bad_cast e) {
			throw new invalid_argument("Date can only be compared to Date objects");
		}

		return returnValue;
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		setCurrentDate()
	//
	//    description:	sets the date from the system clock
	// 
	//    Called By:	constructor
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------
	void Date::setCurrentDate(void)
	{
		time_t rawtime;
		tm *currentTimePtr;
		time(&rawtime);
		currentTimePtr = localtime(&rawtime);

		m_year = currentTimePtr->tm_year + 1900;
		m_month = currentTimePtr->tm_mon;
		m_dayOfMonth = currentTimePtr->tm_mday;
	}

	//-----------------------------------------------------------------------------
	//    Class:			Date
	//    method:			countLeaps(short year)const
	//
	//    description:	returns the number of leap years from 1760 to year
	// 
	//    Calls:            isLeapYear(short)
	// 
	//    Returns:          the number of leap years from 1760 to year 
	//
	//    History Log:
	//                           2/9/08  PB  completed version 1.0
	//-----------------------------------------------------------------------------
	short Date::countLeaps(short year)const
	{
		short leaps = 0;
		for (short i = LOWYEAR; i < year; i++)
			if (isLeapYear(i))
				leaps++;
		return leaps;
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		getDayOfWeek() const
	//
	//    description:	get day of the week (0 - 6) given any date using 
	//					sakamoto's algorithm.
	// 
	//    Calls:		Accessors
	// 
	//    Parameters:	
	//
	//	  Returns:		day index (0 - 6) on day of week
	//
	//    History Log:
	//					02/09/08  PB  completed version 1.0
	//					04/13/17  NP  appeneded to version 1.0
	//-----------------------------------------------------------------------------
	short Date::getDayOfWeek() const
	{
		// Sakamoto's Algorithm
		// https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Sakamoto.27s_methods
		
		static short references[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
		short year = getYear() - (getMonth() < 3);
		return (year + (year / 4) - (year / 100) + (year / 400) + references[getMonth()] + getDayOfMonth()) % 7;
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		getDayOfYear() const
	//
	//    description:	python styled property for getting index of day in year
	// 
	//    Calls:		getDayOfMonth(), daysInMonty(), Accessors
	// 
	//    Parameters:	
	//
	//	  Returns:		totalDays -- int of day index of day in year
	//
	//    History Log:
	//					02/09/08  PB  completed version 1.0
	//					04/13/17  NP  appeneded to version 1.0
	//-----------------------------------------------------------------------------
	short Date::getDayOfYear() const
	{
		short totalDays = getDayOfMonth();
		for (short month = 0; month < getMonth(); month++) {
			totalDays += daysInMonth(m_month, getYear());
		}
		return totalDays;
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		monthName() const
	//
	//    description:	returns string of month name
	// 
	//    Calls:		
	// 
	//    Parameters:	
	//
	//	  Returns:		string -- month name
	//
	//    History Log:
	//					02/09/08  PB  completed version 1.0
	//					04/13/17  NP  appeneded to version 1.0
	//-----------------------------------------------------------------------------
	const string Date::monthName(int monthNum)
	{
		string month;
		switch (monthNum) {
		case 0:
			month = "January";
			break;
		case 1:
			month = "February";
			break;
		case 2:
			month = "March";
			break;
		case 3:
			month = "April";
			break;
		case 4:
			month = "May";
			break;
		case 5:
			month = "June";
			break;
		case 6:
			month = "July";
			break;
		case 7:
			month = "August";
			break;
		case 8:
			month = "September";
			break;
		case 9:
			month = "October";
			break;
		case 10:
			month = "November";
			break;
		case 11:
			month = "December";
			break;
		}
		return month;
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		const string Date::weekdayName()
	//
	//    description:	returns string of day
	// 
	//    Calls:		
	// 
	//    Parameters:	weekday index -- int
	//
	//	  Returns:		string -- day name
	//
	//    History Log:
	//					02/09/08  PB  completed version 1.0
	//					04/13/17  NP  appeneded to version 1.0
	//-----------------------------------------------------------------------------
	const string Date::weekdayName(int weekdayNum)
	{
		string dayOfWeek;
		switch (weekdayNum) {
		case 0:
			dayOfWeek = "Sunday";
			break;
		case 1:
			dayOfWeek = "Monday";
			break;
		case 2:
			dayOfWeek = "Tuesday";
			break;
		case 3:
			dayOfWeek = "Wednesday";
			break;
		case 4:
			dayOfWeek = "Thursday";
			break;
		case 5:
			dayOfWeek = "Friday";
			break;
		case 6:
			dayOfWeek = "Saturday";
			break;
		}
		return dayOfWeek;
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		setDayOfMonth(short dayOfMonth)
	//
	//    description:	mutator for m_dayOfMonth
	// 
	//    Calls:            daysInMonth(short, short)
	// 
	//    Parameters:	dayOfMonth --  day of month to set
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	//-----------------------------------------------------------------------------
	void Date::setDayOfMonth(short dayOfMonth)
	{
		if (dayOfMonth > 0
			&& dayOfMonth <= daysInMonth(m_month, m_year))
		{
			m_dayOfMonth = dayOfMonth;
		}
		else {
			m_dayOfMonth = 1;
		}
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		setMonth(short dmonth)
	//
	//    description:	mutator for m_month
	// 
	//    Calls:        daysInMonth(short, short)
	// 
	//    Parameters:	month --  month to set
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	//-----------------------------------------------------------------------------
	void Date::setMonth(short month)
	{
		if (month > 0 && month < MONTHSINYEAR)
			m_month = month;
		else
			m_month = 0;
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		setYear(short year)
	//
	//    description:	mutator for m_year
	// 
	//    Calls:        isLeapYear(short)
	// 
	//    Parameters:	year --  year to set
	//
	//    History Log:
	//			 2/9/08  PB  completed version 1.0
	//-----------------------------------------------------------------------------
	void Date::setYear(short year)
	{
		if (year > LOWYEAR)
			m_year = year;
		else
			m_year = LOWYEAR;
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		input(istream & sin)
	//
	//    description:	reads DD/MM/YYYY from istream and sets values in Date object
	// 
	//    Parameters:	istream & sin  -- the istream to read from
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	istream & operator >>
	// 
	//	  Calls:		Mutators of Date
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
	void Date::input(istream& sin)
	{
		bool reset = false;
		short day, month, year;
		char c;

		sin >> day;
		sin.get(c);
		if (c != '/') { reset = true; }

		sin >> month;
		sin.get(c);
		if (c != '/') { reset = true; }

		sin >> year;

		if (reset) {
			day = month = year = 0;
		}
		else {
			if (year < LOWYEAR)
				year = LOWYEAR;
			if (month < 0 || month >= MONTHSINYEAR)
				month = 0;
			if (day < 1 || day >= daysInMonth(month, year))
				day = 0;
		}
		setDayOfMonth(day);
		setMonth(month);
		setYear(year);
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		print(ostream & sout) const
	//
	//    description:	prints text in DD/MM/YYYY to specified ostream
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
	void Date::print(ostream& sout)const
	{
		sout << m_dayOfMonth << '/' << m_month << '/' << m_year;
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		ostream & operator << (ostream & sout, Date & date)
	//
	//    description:	invoke print and pass in sout into it
	// 
	//    Parameters:	ostream & sout -- ostream you'd like to print to
	//					Date & date -- date object you'd like to write to
	//
	//	  Programmers:  Norton Pengra
	//
	//    Called By:	main
	//
	//	  Calls:		Date::print
	// 
	//    Returns:      the ostream reference initially passed in
	//
	//    History Log:
	//			04/11/17  NP  appended to version 1.1
	//-----------------------------------------------------------------------------
	ostream & operator<<(ostream & sout, const Date & date)
	{
		date.print(sout);
		return sout;
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		ostream & operator >> (istream & sin, Date & date)
	//
	//    description:	read from the specified input stream and write to date obj
	// 
	//    Parameters:	istream & sin -- istream you'd like to read from
	//					Date & date -- date object you'd like to write to
	//
	//	  Programmers:  Norton Pengra
	//
	//    Called By:	main
	//
	//	  Calls:		Date::input
	// 
	//    Returns:      the istream reference initially passed in
	//
	//    History Log:
	//			04/11/17  NP  appended to version 1.1
	//-----------------------------------------------------------------------------
	istream & operator>>(istream & sin, Date & date)
	{
		sin >> date;
		return sin;
	}

}
