#include "stdafx.h"
#include "CppUnitTest.h"


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
			date1.setMonth(1);
			//Assert::AreEqual(LOWYEAR, date1.getYear());
			//Assert::AreEqual((short)1, date1.getMonth());
			//Assert::AreEqual((short)28, date1.getDayOfMonth());
		}

		// Static tests

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