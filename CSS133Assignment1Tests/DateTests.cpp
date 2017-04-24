#include "stdafx.h"
#include "CppUnitTest.h"
#include <string.h>
#include <iostream>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NP_DATETIME;

namespace CSS133Assignment1Tests
{
	TEST_CLASS(DateTests)
	{
	public:

		// Constructor tests

		TEST_METHOD(emptyConstructor) {
			Date today;
			Assert::IsTrue(isToday(today));
		}

		TEST_METHOD(InvalidConstructor) {
			Date today((short)99999, (short)236236, (short)-236);
			Assert::IsTrue(isToday(today));
		}

		// Minimum tests

		TEST_METHOD(minDateTest) {
			Date date1(0, 0, LOWYEAR);
			Assert::AreEqual(LOWYEAR, date1.getYear());
			Assert::AreEqual((short)0, date1.getMonth());
			Assert::AreEqual((short)0, date1.getDayOfMonth());
		}

		TEST_METHOD(minUnderflowDayDateTest) {
			Date date1(-1, 0, LOWYEAR);
			Assert::AreEqual(LOWYEAR, date1.getYear());
			Assert::AreEqual((short)0, date1.getMonth());
			Assert::AreEqual(currentDate(), date1.getDayOfMonth());
		}

		TEST_METHOD(minUnderflowDayMonthTest) {
			Date date1(0, -1, LOWYEAR);
			Assert::AreEqual(LOWYEAR, date1.getYear());
			Assert::AreEqual(currentMonth(), date1.getMonth());
			Assert::AreEqual((short)0, date1.getDayOfMonth());
		}

		TEST_METHOD(minUnderflowDayYearTest) {
			Date date1(0, 0, LOWYEAR - 1);
			Assert::AreEqual(currentYear(), date1.getYear());
			Assert::AreEqual((short)0, date1.getMonth());
			Assert::AreEqual((short)0, date1.getDayOfMonth());
		}

		// Test Invalid Operations

		TEST_METHOD(minFixDatefromMonth) {
			Date date1(30, 0, LOWYEAR);
			Assert::AreEqual(LOWYEAR, date1.getYear());
			Assert::AreEqual((short)0, date1.getMonth());
			Assert::AreEqual((short)30, date1.getDayOfMonth());
		}

		// Set to feb 1st, then change the day to march, 31st
		// then set to feb 1st again
		TEST_METHOD(setLowDayMaxAndChange) {
			Date date1(0, 1);
			Assert::AreEqual(currentYear(), date1.getYear());
			Assert::AreEqual((short)1, date1.getMonth());
			Assert::AreEqual((short)0, date1.getDayOfMonth());

			date1.setMonth(2);
			date1.setDayOfMonth(30);
			Assert::AreEqual(currentYear(), date1.getYear());
			Assert::AreEqual((short)2, date1.getMonth());
			Assert::AreEqual((short)30, date1.getDayOfMonth());

			date1.setMonth(1);
			Assert::AreEqual(currentYear(), date1.getYear());
			Assert::AreEqual((short)1, date1.getMonth());
			Assert::AreEqual((short)27, date1.getDayOfMonth());

			date1.setDayOfMonth(30);
			Assert::AreEqual(currentYear(), date1.getYear());
			Assert::AreEqual((short)1, date1.getMonth());
			Assert::AreEqual((short)27, date1.getDayOfMonth());
		}

		// tomorrow tests

		TEST_METHOD(RegMonthEndTomorrowTests) {
			Date date1(29, 0, 2017);
			Assert::AreEqual((short)2017, date1.getYear());
			Assert::AreEqual((short)0, date1.getMonth());
			Assert::AreEqual((short)29, date1.getDayOfMonth());

			Date date2 = date1.tomorrow();
			Assert::AreEqual((short)2017, date2.getYear());
			Assert::AreEqual((short)0, date2.getMonth());
			Assert::AreEqual((short)30, date2.getDayOfMonth());

			Date date3 = date2.tomorrow();
			Assert::AreEqual((short)2017, date3.getYear());
			Assert::AreEqual((short)1, date3.getMonth());
			Assert::AreEqual((short)0, date3.getDayOfMonth());
		}

		TEST_METHOD(FebLeapYearEndTomorrowTests) {
			Date date1(26, 1, 1760);
			Assert::AreEqual((short)1760, date1.getYear());
			Assert::AreEqual((short)1, date1.getMonth());
			Assert::AreEqual((short)26, date1.getDayOfMonth());

			Date date2 = date1.tomorrow();
			Assert::AreEqual((short)1760, date2.getYear());
			Assert::AreEqual((short)1, date2.getMonth());
			Assert::AreEqual((short)27, date2.getDayOfMonth());

			Date date3 = date2.tomorrow();
			Assert::AreEqual((short)1760, date3.getYear());
			Assert::AreEqual((short)1, date3.getMonth());
			Assert::AreEqual((short)28, date3.getDayOfMonth());

			Date date4 = date3.tomorrow();
			Assert::AreEqual((short)1760, date4.getYear());
			Assert::AreEqual((short)2, date4.getMonth());
			Assert::AreEqual((short)0, date4.getDayOfMonth());
		}

		TEST_METHOD(FebEndTomorrowTests) {
			Date date1(26, 1, 1761);
			Assert::AreEqual((short)1761, date1.getYear());
			Assert::AreEqual((short)1, date1.getMonth());
			Assert::AreEqual((short)26, date1.getDayOfMonth());

			Date date2 = date1.tomorrow();
			Assert::AreEqual((short)1761, date2.getYear());
			Assert::AreEqual((short)1, date2.getMonth());
			Assert::AreEqual((short)27, date2.getDayOfMonth());

			Date date3 = date2.tomorrow();
			Assert::AreEqual((short)1761, date3.getYear());
			Assert::AreEqual((short)2, date3.getMonth());
			Assert::AreEqual((short)0, date3.getDayOfMonth());
		}

		TEST_METHOD(Dec31TomorrowTests) {
			Date date1(30, 11, 1760);

			Date date2 = date1.tomorrow();
			Assert::AreEqual((short)1761, date2.getYear());
			Assert::AreEqual((short)0, date2.getMonth());
			Assert::AreEqual((short)0, date2.getDayOfMonth());
		}

		// Yesterday tests

		TEST_METHOD(RegMonthYesterdayTest) {
			Date date1(1, 0, 2017);
			Date date2 = date1.yesterday();

			Assert::AreEqual((short)2017, date2.getYear());
			Assert::AreEqual((short)0, date2.getMonth());
			Assert::AreEqual((short)0, date2.getDayOfMonth());
		}

		TEST_METHOD(MarchMonthYesterdayTest) {
			Date date1(1, 2, 2017);
			Date date2 = date1.yesterday();
			Date date3 = date2.yesterday();

			Assert::AreEqual((short)2017, date2.getYear());
			Assert::AreEqual((short)2, date2.getMonth());
			Assert::AreEqual((short)0, date2.getDayOfMonth());

			Assert::AreEqual((short)2017, date3.getYear());
			Assert::AreEqual((short)1, date3.getMonth());
			Assert::AreEqual((short)27, date3.getDayOfMonth());
		}

		TEST_METHOD(MarchMonthLeapYearYesterdayTest) {
			Date date1(1, 2, 2000);
			Date date2 = date1.yesterday();
			Date date3 = date2.yesterday();

			Assert::AreEqual((short)2000, date2.getYear());
			Assert::AreEqual((short)2, date2.getMonth());
			Assert::AreEqual((short)0, date2.getDayOfMonth());

			Assert::AreEqual((short)2000, date3.getYear());
			Assert::AreEqual((short)1, date3.getMonth());
			Assert::AreEqual((short)28, date3.getDayOfMonth());
		}

		TEST_METHOD(JanYearYesterdayTest) {
			Date date1(0, 0, 2000);
			Date date2 = date1.yesterday();
			Date date3 = date2.yesterday();

			Assert::AreEqual((short)1999, date2.getYear());
			Assert::AreEqual((short)11, date2.getMonth());
			Assert::AreEqual((short)30, date2.getDayOfMonth());

			Assert::AreEqual((short)1999, date3.getYear());
			Assert::AreEqual((short)11, date3.getMonth());
			Assert::AreEqual((short)29, date3.getDayOfMonth());
		}

		// Static tests

		TEST_METHOD(testMonthName) {
			Assert::AreEqual(string("January"), Date::monthName(0));
			Assert::AreEqual(string("February"), Date::monthName(1));
			Assert::AreEqual(string("March"), Date::monthName(2));
			Assert::AreEqual(string("April"), Date::monthName(3));
			Assert::AreEqual(string("May"), Date::monthName(4));
			Assert::AreEqual(string("June"), Date::monthName(5));
			Assert::AreEqual(string("July"), Date::monthName(6));
			Assert::AreEqual(string("August"), Date::monthName(7));
			Assert::AreEqual(string("September"), Date::monthName(8));
			Assert::AreEqual(string("October"), Date::monthName(9));
			Assert::AreEqual(string("November"), Date::monthName(10));
			Assert::AreEqual(string("December"), Date::monthName(11));
			Assert::AreEqual(string("Invalid"), Date::monthName(12));
			Assert::AreEqual(string("Invalid"), Date::monthName(-1));
		}

		TEST_METHOD(testWeekName) {
			Assert::AreEqual(string("Sunday"), Date::weekdayName(0));
			Assert::AreEqual(string("Monday"), Date::weekdayName(1));
			Assert::AreEqual(string("Tuesday"), Date::weekdayName(2));
			Assert::AreEqual(string("Wednesday"), Date::weekdayName(3));
			Assert::AreEqual(string("Thursday"), Date::weekdayName(4));
			Assert::AreEqual(string("Friday"), Date::weekdayName(5));
			Assert::AreEqual(string("Saturday"), Date::weekdayName(6));
			Assert::AreEqual(string("Invalid"), Date::weekdayName(7));
			Assert::AreEqual(string("Invalid"), Date::weekdayName(-1));
		}

		TEST_METHOD(testDaysInMonth) {
			short year = 2017;
			Assert::AreEqual((short)31, Date::daysInMonth(0, year));
			Assert::AreEqual((short)28, Date::daysInMonth(1, year));
			Assert::AreEqual((short)31, Date::daysInMonth(2, year));
			Assert::AreEqual((short)30, Date::daysInMonth(3, year));
			Assert::AreEqual((short)31, Date::daysInMonth(4, year));
			Assert::AreEqual((short)30, Date::daysInMonth(5, year));
			Assert::AreEqual((short)31, Date::daysInMonth(6, year));
			Assert::AreEqual((short)31, Date::daysInMonth(7, year));
			Assert::AreEqual((short)30, Date::daysInMonth(8, year));
			Assert::AreEqual((short)31, Date::daysInMonth(9, year));
			Assert::AreEqual((short)30, Date::daysInMonth(10, year));
			Assert::AreEqual((short)31, Date::daysInMonth(11, year));
		}

		TEST_METHOD(testDaysInMonthLeapYear) {
			short year = 2000;
			Assert::AreEqual((short)31, Date::daysInMonth(0, year));
			Assert::AreEqual((short)29, Date::daysInMonth(1, year));
			Assert::AreEqual((short)31, Date::daysInMonth(2, year));
			Assert::AreEqual((short)30, Date::daysInMonth(3, year));
			Assert::AreEqual((short)31, Date::daysInMonth(4, year));
			Assert::AreEqual((short)30, Date::daysInMonth(5, year));
			Assert::AreEqual((short)31, Date::daysInMonth(6, year));
			Assert::AreEqual((short)31, Date::daysInMonth(7, year));
			Assert::AreEqual((short)30, Date::daysInMonth(8, year));
			Assert::AreEqual((short)31, Date::daysInMonth(9, year));
			Assert::AreEqual((short)30, Date::daysInMonth(10, year));
			Assert::AreEqual((short)31, Date::daysInMonth(11, year));
		}

		TEST_METHOD(testCountLeapYears) {
			Date date1;
			Assert::AreEqual((short)1, date1.countLeaps(1760));
			Assert::AreEqual((short)2, date1.countLeaps(1764));
			Assert::AreEqual((short)3, date1.countLeaps(1768));
			Assert::AreEqual((short)4, date1.countLeaps(1772));
			Assert::AreEqual((short)36, date1.countLeaps(1908));
			Assert::AreEqual((short)58, date1.countLeaps(1996));
			Assert::AreEqual((short)59, date1.countLeaps(2000));
		}

		TEST_METHOD(testLeapYears) {
			Date date1(-1, -1, 2017);
			Assert::IsFalse(date1.isLeapYear(2017));
			Assert::IsTrue(date1.isLeapYear(2020));
			Assert::IsTrue(date1.isLeapYear(2016));
			Assert::IsFalse(date1.isLeapYear(1900));
			Assert::IsTrue(date1.isLeapYear(1760));
		}


	private:
		short currentDate() {
			time_t rawtime;
			tm rightnow;
			time(&rawtime);
			rightnow = *localtime(&rawtime);

			return rightnow.tm_mday;
		}

		short currentMonth() {
			time_t rawtime;
			tm rightnow;
			time(&rawtime);
			rightnow = *localtime(&rawtime);

			return rightnow.tm_mon;
		}

		short currentYear() {
			time_t rawtime;
			tm rightnow;
			time(&rawtime);
			rightnow = *localtime(&rawtime);

			return rightnow.tm_year + 1900;
		}

		bool isToday(Date date) {
			time_t rawtime;
			tm rightnow;
			time(&rawtime);
			rightnow = * localtime(&rawtime);

			bool yearMatch = ((short)(rightnow.tm_year + 1900) == date.getYear());
			bool monthMatch = ((short)(rightnow.tm_mon) == date.getMonth());
			bool dayMatch = ((short)(rightnow.tm_mday) == date.getDayOfMonth());
			return yearMatch && monthMatch && dayMatch;
		}

		void validateDate(Date date) {
		}

	};
}