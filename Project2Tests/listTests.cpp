#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Project2\list.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NP_ADT;

namespace Project2Tests
{		
	TEST_CLASS(CDLLTests)
	{
	public:
		
		TEST_METHOD(ConstructorTest)
		{
			auto temp = CDLL<int>();
			// Assert::IsNull(temp.head());
			// Assert::IsNull(temp.tail());
		}

	};
}