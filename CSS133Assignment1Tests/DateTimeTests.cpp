#include "stdafx.h"
#include "CppUnitTest.h"
// #include "..\CS133Assignment1\Comparable.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NP_DATETIME;

namespace CSS133Assignment1Tests
{
	TEST_CLASS(CTimeTests)
	{
	public:

		// Constructor tests

		TEST_METHOD(emptyConstructor) {
			DateTime date1;
			Assert::AreEqual(currentDate(), date1.getDayOfMonth());
			Assert::AreEqual(currentMonth(), date1.getMonth());
			Assert::AreEqual(currentYear(), date1.getYear());
			validateTime(date1);
		}

		TEST_METHOD(secondaryConstructor) {
			DateTime date1(1);
			Assert::AreEqual(short(1), date1.getDayOfMonth());
			Assert::AreEqual(short(0), date1.getMonth());
			Assert::AreEqual(LOWYEAR, date1.getYear());
			Assert::AreEqual(short(0), date1.getHour());
			Assert::AreEqual(short(0), date1.getMinute());
			Assert::AreEqual(short(0), date1.getSecond());
		}

		// Comparison tests

		TEST_METHOD(MinimumComparisonTest)
		{
			DateTime date1(0, 0, LOWYEAR, 0, 0, 0);
			DateTime date2(0, 0, LOWYEAR, 0, 0, 0);
			Assert::IsTrue(date1 == date2);
			Assert::IsTrue(date1 <= date2);
			Assert::IsTrue(date1 >= date2);
			Assert::IsTrue(date2 <= date1);
			Assert::IsTrue(date2 >= date1);
		}

		TEST_METHOD(DateLTComparisonTest)
		{
			DateTime date1(0);
			DateTime date2(0);

			for (short hour = 1; hour < 24; hour++) {
				date2.setHour(hour);
				Assert::IsTrue(date1 < date2);
				Assert::IsTrue(date1 <= date2);
				Assert::IsTrue(date2 > date1);
				Assert::IsTrue(date2 >= date1);
			}

		}

	private:
		void validateTime(CTime time) {
			Assert::IsTrue(time.getHour() >= 0 && time.getHour() < 24);
			Assert::IsTrue(time.getMinute() >= 0 && time.getMinute() < 60);
			Assert::IsTrue(time.getSecond() >= 0 && time.getSecond() < 60);
		}

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
			rightnow = *localtime(&rawtime);

			bool yearMatch = ((short)(rightnow.tm_year + 1900) == date.getYear());
			bool monthMatch = ((short)(rightnow.tm_mon) == date.getMonth());
			bool dayMatch = ((short)(rightnow.tm_mday) == date.getDayOfMonth());
			return yearMatch && monthMatch && dayMatch;
		}
	};
}