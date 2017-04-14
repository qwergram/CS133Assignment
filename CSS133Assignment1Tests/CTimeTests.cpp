#include "stdafx.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NP_DATETIME;

namespace CSS133Assignment1Tests
{		
	TEST_CLASS(CTimeTests)
	{
	public:
		
		TEST_METHOD(ConstructorTest)
		{
			CTime x = CTime();
		}

	};
}