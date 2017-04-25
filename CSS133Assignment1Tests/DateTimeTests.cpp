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

		TEST_METHOD(EmptyConstructorTest)
		{
			DateTime date1(0, 0, LOWYEAR, 0, 0, 0);
			DateTime date2(0, 0, LOWYEAR, 0, 0, 0);
			Assert::IsTrue(date1 == date2);
		}
	};
}