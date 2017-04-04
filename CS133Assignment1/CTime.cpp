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
namespace PB_DATETIME
{
//-----------------------------------------------------------------------------
//    Class:		CTime
//			method:		setCurrentTime()
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
	// and so on...
}
