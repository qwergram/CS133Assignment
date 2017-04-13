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
		setMonth(month);
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
	void Date::input(istream& sin)
	{

	}
	//-----------------------------------------------------------------------------
	void Date::print(ostream& sout)const
	{
		sout << m_dayOfMonth << '/' << m_month << '/' << m_year;
	}

}
