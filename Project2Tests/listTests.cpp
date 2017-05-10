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

		TEST_METHOD(TestPushFrontConnections) 
		{
			CDLL<int> test = CDLL<int>();
			test.push_front(5);
			test.push_front(0);

			Assert::IsTrue(test.head() == test.head()->next->prev);
			Assert::IsTrue(test.head() == test.head()->prev->next);
			Assert::IsTrue(test.tail() == test.tail()->next->prev);
			Assert::IsTrue(test.tail() == test.tail()->prev->next);
		}

		TEST_METHOD(TestPushBackConnections)
		{
			CDLL<int> test = CDLL<int>();
			test.push_back(5);
			test.push_back(0);

			Assert::IsTrue(test.head() == test.head()->next->prev);
			Assert::IsTrue(test.head() == test.head()->prev->next);
			Assert::IsTrue(test.tail() == test.tail()->next->prev);
			Assert::IsTrue(test.tail() == test.tail()->prev->next);
		}

		TEST_METHOD(TestOnePushFrontItemList) {
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

		TEST_METHOD(TestTwoPushFrontItemList) {
			CDLL<int> test = CDLL<int>();
			test.push_front(0);
			test.push_front(1);
			// <-> 1 <-> 0 <->

			CDLL<int>::node * thisThing = test.head();

			Assert::AreEqual(unsigned int(2), test.getSize());
			
			Assert::IsTrue(unsigned int(1) == test.head()->data);
			Assert::IsTrue(unsigned int(0) == test.tail()->data);
			
			
			CDLL<int>::node * ptr = test.head();				// == 1
			CDLL<int>::node * nextPtr = test.head()->next;		// == 0
			CDLL<int>::node * doubleNextPtr = nextPtr->next;	// == 1
			CDLL<int>::node * prevPtr = test.head()->prev;		// == 0
			CDLL<int>::node * doublePrevPtr = prevPtr->prev;	// == 1

			Assert::IsTrue(ptr == doubleNextPtr);
			Assert::IsTrue(nextPtr == prevPtr);
			Assert::IsTrue(doubleNextPtr == doublePrevPtr);
			Assert::IsTrue(ptr != nextPtr);
		}

		TEST_METHOD(TestThreePushFrontItemList) {
			CDLL<int> test = CDLL<int>();
			test.push_front(0);
			test.push_front(1);
			test.push_front(2);
			// <-> 2 <-> 1 <-> 0 <->

			CDLL<int>::node * thisThing = test.head();

			Assert::AreEqual(unsigned int(3), test.getSize());

			Assert::IsTrue(unsigned int(2) == test.head()->data);
			Assert::IsTrue(unsigned int(0) == test.tail()->data);

			CDLL<int>::node * ptr = test.head();				// == 2
			CDLL<int>::node * nextPtr = test.head()->next;		// == 1
			CDLL<int>::node * doubleNextPtr = nextPtr->next;	// == 0
			CDLL<int>::node * prevPtr = test.head()->prev;		// == 0
			CDLL<int>::node * doublePrevPtr = prevPtr->prev;	// == 1

			Assert::IsTrue(ptr == doubleNextPtr->next);
			Assert::IsTrue(nextPtr == doublePrevPtr);
			Assert::IsTrue(prevPtr == doubleNextPtr);
			Assert::IsTrue(ptr != nextPtr);
			Assert::IsTrue(nextPtr != doubleNextPtr);
		}

		TEST_METHOD(TestOnePushBackItemList) {
			CDLL<int> test = CDLL<int>();
			test.push_back(0);

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

		TEST_METHOD(TestTwoPushBackItemList) {
			CDLL<int> test = CDLL<int>();
			test.push_back(0);
			test.push_back(1);
			// <-> 0 <-> 1 <->

			CDLL<int>::node * thisThing = test.head();

			Assert::AreEqual(unsigned int(2), test.getSize());

			Assert::IsTrue(unsigned int(0) == test.head()->data);
			Assert::IsTrue(unsigned int(1) == test.tail()->data);


			CDLL<int>::node * ptr = test.head();				// == 0
			CDLL<int>::node * nextPtr = test.head()->next;		// == 1
			CDLL<int>::node * doubleNextPtr = nextPtr->next;	// == 0
			CDLL<int>::node * prevPtr = test.head()->prev;		// == 1
			CDLL<int>::node * doublePrevPtr = prevPtr->prev;	// == 0

			Assert::IsTrue(ptr == doubleNextPtr);
			Assert::IsTrue(nextPtr == prevPtr);
			Assert::IsTrue(doubleNextPtr == doublePrevPtr);
			Assert::IsTrue(ptr != nextPtr);
		}

		TEST_METHOD(TestThreePushBackItemList) {
			CDLL<int> test = CDLL<int>();
			test.push_back(0);
			test.push_back(1);
			test.push_back(2);
			// <-> 0 <-> 1 <-> 2 <->

			CDLL<int>::node * thisThing = test.head();

			Assert::AreEqual(unsigned int(3), test.getSize());

			Assert::IsTrue(unsigned int(0) == test.head()->data);
			Assert::IsTrue(unsigned int(2) == test.tail()->data);

			CDLL<int>::node * ptr = test.head();				// == 0
			CDLL<int>::node * nextPtr = test.head()->next;		// == 1
			CDLL<int>::node * doubleNextPtr = nextPtr->next;	// == 2
			CDLL<int>::node * prevPtr = test.head()->prev;		// == 2
			CDLL<int>::node * doublePrevPtr = prevPtr->prev;	// == 0

			Assert::IsTrue(ptr == doubleNextPtr->next);
			Assert::IsTrue(nextPtr == doublePrevPtr);
			Assert::IsTrue(prevPtr == doubleNextPtr);
			Assert::IsTrue(ptr != nextPtr);
			Assert::IsTrue(nextPtr != doubleNextPtr);
		}
	};
}