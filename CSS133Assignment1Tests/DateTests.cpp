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
			Date today(99999, 236236, -236);
			Assert::IsTrue(isToday(today));
		}

		// Accessor and Mutator tests

		TEST_METHOD(minDateTest) {
			Date date1(0, 0, LOWYEAR);
			Assert::AreEqual(LOWYEAR, date1.getYear());
			Assert::AreEqual((short)0, date1.getMonth());
			Assert::AreEqual((short)0, date1.getDayOfMonth());
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