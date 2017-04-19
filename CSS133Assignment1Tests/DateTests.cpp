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
		void validateDate(Date date) {
		}

	};
}