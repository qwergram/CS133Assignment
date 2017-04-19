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


	private:
		void validateDate(Date time) {
			Assert::IsTrue(time.getHour() >= 0 && time.getHour() < 24);
			Assert::IsTrue(time.getMinute() >= 0 && time.getMinute() < 60);
			Assert::IsTrue(time.getSecond() >= 0 && time.getSecond() < 60);
		}

	};
}