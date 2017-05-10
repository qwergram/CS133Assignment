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
			Assert::IsTrue(test.head() == test.tail());
		}

		TEST_METHOD(TestOneItemList) {
			CDLL<int> test = CDLL<int>();
			test.push_front(0);
			
			CDLL<int>::node * thisThing = test.head();

			Assert::AreEqual(unsigned int(1), test.getSize());
			Assert::IsTrue(unsigned int(0) == test.tail()->data);
			
			CDLL<int>::node * ptr = test.head();
			CDLL<int>::node * nextPtr = test.head()->next;
			CDLL<int>::node * doubleNextPtr = nextPtr->next;
			CDLL<int>::node * prevPtr = test.head()->prev;
			CDLL<int>::node * doublePrevPtr = prevPtr->prev;

			Assert::IsTrue(ptr == nextPtr);
			Assert::IsTrue(nextPtr == doubleNextPtr);
			Assert::IsTrue(doubleNextPtr == prevPtr);
			Assert::IsTrue(prevPtr == doublePrevPtr);
		}

		TEST_METHOD(TestTwoItemList) {
			CDLL<int> test = CDLL<int>();
			test.push_front(0);
			test.push_front(1);
			// <-> 1 <-> 0 <->

			CDLL<int>::node * thisThing = test.head();

			Assert::AreEqual(unsigned int(2), test.getSize());
			Assert::IsTrue(unsigned int(0) == test.tail()->data);
			unsigned int x = test.head()->data;
			unsigned int y = test.tail()->data;
			Assert::IsTrue(unsigned int(1) == test.head()->data);

			CDLL<int>::node * ptr = test.head();
			CDLL<int>::node * nextPtr = test.head()->next;
			CDLL<int>::node * doubleNextPtr = nextPtr->next;
			CDLL<int>::node * prevPtr = test.head()->prev;
			CDLL<int>::node * doublePrevPtr = prevPtr->prev;

			/*Assert::IsTrue(ptr == doubleNextPtr);
			Assert::IsTrue(nextPtr == doubleNextPtr);
			Assert::IsTrue(doubleNextPtr == prevPtr);
			Assert::IsTrue(prevPtr == doublePrevPtr);*/
		}
	};
}