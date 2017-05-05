#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Project2\list.h"
#include "..\Project2\list.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NP_ADT;

namespace Project2Tests
{		
	TEST_CLASS(ListTests)
	{
	public:
		
		TEST_METHOD(TestEmptyConstructor)
		{
			CDLL<int> test = CDLL<int>();
			Assert::AreEqual(unsigned int(0), test.getSize());
			Assert::IsTrue(nullptr == test.head());
			Assert::IsTrue(nullptr == test.tail());
		}

		TEST_METHOD(TestOneItemList) {
			CDLL<int> test = CDLL<int>();
			test.push_front(0);
			
			CDLL<int>::node * thisThing = test.head();

			Assert::AreEqual(unsigned int(1), test.getSize());
			Assert::IsTrue(unsigned int(0) == test.tail()->data);
			
			for (int i = 0; i <= 20; i++) {
				thisThing = thisThing->next;
				Assert::IsTrue(unsigned int(0) == thisThing->data);
			}
		}

	};
}