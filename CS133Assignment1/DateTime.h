//-----------------------------------------------------------------------------
//	File: DateTime.h
//
//	class: DateTime
//-----------------------------------------------------------------------------
#ifndef DATETIME_H
#define DATETIME_H
#include "Date.h"
#include "CTime.h"

class DateTime : Date, CTime {
public:

	DateTime();
	DateTime(short dayOfMonth, short month = 0, short year = 0, short hour = 0, short minute = 0, short second = 0);
	DateTime(const Date & date, const CTime & time);

	// pure virtuals that MUST be defined
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
	virtual void input(istream& sin);
	virtual void print(ostream& sout)const;

private:
	Date m_date;
	CTime m_time;

};

#endif