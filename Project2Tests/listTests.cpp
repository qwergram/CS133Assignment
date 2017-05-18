#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Project2\list.h"
#include "..\Project2\list.cpp"
#include "..\Project2\queue.h"
#include "..\Project2\queue.cpp"
#include "..\Project2\public_queue.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NP_ADT;

namespace Project2Tests
{	
	TEST_CLASS(PublicQueueTests)
	{
	public:

		TEST_METHOD(PublicQueue_TestEmptyConstructor)
		{
			PublicQueue<int> test = PublicQueue<int>();
			Assert::AreEqual(unsigned int(0), test.getSize());
			Assert::IsTrue(nullptr == test.head());
			Assert::IsTrue(nullptr == test.tail());
			Assert::IsTrue(test.empty());
		}

		TEST_METHOD(PublicQueue_TestPushConnections)
		{
			PublicQueue<int> test = PublicQueue<int>();
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			auto x = 5;
			auto y = 0;
			test.push(x);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(1), test.getSize());
			test.push(y);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(2), test.getSize());

			Assert::IsTrue(test.head() == test.head()->next->prev);
			Assert::IsTrue(test.head() == test.head()->prev->next);
			Assert::IsTrue(test.tail() == test.tail()->next->prev);
			Assert::IsTrue(test.tail() == test.tail()->prev->next);
		}

		TEST_METHOD(PublicQueue_TestOnePushItemPublicQueue) {
			PublicQueue<int> test = PublicQueue<int>();
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			auto x = 5;
			auto y = 0;
			test.push(y);
			Assert::IsFalse(test.empty());

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

		TEST_METHOD(PublicQueue_TestTwoPushItemPublicQueue) {
			PublicQueue<int> test = PublicQueue<int>();
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			auto x = 5;
			auto y = 0;
			test.push(y);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(1), test.getSize());
			test.push(x);
			Assert::IsFalse(test.empty());
			// <-> 0 <-> 1 <->

			CDLL<int>::node * thisThing = test.head();

			Assert::AreEqual(unsigned int(2), test.getSize());

			Assert::AreEqual(y, test.head()->data);
			Assert::AreEqual(x, test.tail()->data);


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

		TEST_METHOD(PublicQueue_TestThreePushItemPublicQueue) {
			PublicQueue<int> test = PublicQueue<int>();
			auto x = 0;
			auto y = 1;
			auto z = 2;
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push(x);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(1), test.getSize());
			test.push(y);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(2), test.getSize());
			test.push(z);
			Assert::IsFalse(test.empty());
			// <-> 0 <-> 1 <-> 2 <->

			CDLL<int>::node * thisThing = test.head();

			Assert::AreEqual(unsigned int(3), test.getSize());

			Assert::AreEqual(x, test.head()->data);
			Assert::AreEqual(z, test.tail()->data);

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

		TEST_METHOD(PublicQueue_TestPopEmptyPublicQueue) {
			bool exceptionThrown = false;
			auto test = PublicQueue<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			try {
				test.pop();
			}
			catch (runtime_error) {
				exceptionThrown = true;
			}
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(PublicQueue_TestPopAfterPush) {
			auto test = PublicQueue<int>();
			auto x = 1;
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			test.push(x);
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::AreEqual(1, test.pop());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(PublicQueue_TestPopAfterTwoPush) {
			auto test = PublicQueue<int>();
			auto x = 1;
			auto y = 2;
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			test.push(x);
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			test.push(y);
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::AreEqual(1, test.pop());
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::AreEqual(2, test.pop());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(PublicQueue_TestPopFrontAfterThreePush) {
			auto test = PublicQueue<int>();
			auto x = 1;
			auto y = 2;
			auto z = 3;
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			test.push(x);
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			test.push(y);
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			test.push(z);
			Assert::AreEqual(unsigned(3), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::AreEqual(1, test.pop());
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::AreEqual(2, test.pop());
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::AreEqual(3, test.pop());
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(PublicQueue_TestReleaseAndDestructor) {
			auto test = PublicQueue<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			for (int x = 0; x < 1000; x++) {
				test.push(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}
			Assert::IsTrue(test.getSize() == 1000);
			Assert::IsFalse(test.empty());
			test.release();
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
		}

		TEST_METHOD(PublicQueue_TestCopyConstructorEmpty) {
			auto test = PublicQueue<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			bool exceptionThrown = false;
			try {
				auto test2 = PublicQueue<int>(test);
			}
			catch (...) {
				exceptionThrown = true;
			}
			Assert::IsFalse(exceptionThrown);
			Assert::AreEqual(unsigned(0), test.getSize());
		}

		TEST_METHOD(PublicQueue_TestCopyConstructor) {
			auto test = PublicQueue<int>();
			auto x = 4;
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push(x);
			Assert::AreEqual(unsigned(1), test.getSize());

			auto test2 = PublicQueue<int>(test);
			Assert::AreEqual(unsigned(1), test2.getSize());
			Assert::IsFalse(&(test.head()->data) == &(test2.head()->data));
			Assert::IsTrue(test.head()->data == test2.head()->data);
		}

		TEST_METHOD(PublicQueue_TestCopyObjectConstructor) {
			class Dummy {
			public:
				Dummy(int x) : m_x(x) {};
				int m_x = 0;
			};

			auto test = PublicQueue<Dummy>();
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push(Dummy(5));
			Assert::AreEqual(unsigned(1), test.getSize());

			auto test2 = PublicQueue<Dummy>(test);
			Assert::AreEqual(unsigned(1), test2.getSize());
			Assert::IsFalse(&(test.head()->data) == &(test2.head()->data));
			Assert::IsTrue(test.head()->data.m_x == test2.head()->data.m_x);
		}

		TEST_METHOD(PublicQueue_TestIteratorPreIncrementOperator) {
			auto test = PublicQueue<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			for (int x = 0; x < 100; x++) {
				test.push(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}

			auto r_it = test.begin();
			for (int x = 0; x < 99; x++) {
				Assert::IsTrue(*++r_it == x + 1);
			}
			Assert::IsTrue(*++r_it == 0);
			Assert::IsTrue(*++r_it == 1);
			Assert::AreEqual(unsigned(100), test.getSize());
		}

		TEST_METHOD(PublicQueue_TestIteratorPostIncrementOperator) {
			auto test = PublicQueue<int>();
			for (int x = 0; x < 100; x++) {
				test.push(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}

			auto r_it = test.begin();
			for (int x = 0; x < 100; x++) {
				Assert::IsTrue(*r_it++ == x);
			}
			Assert::IsTrue(*r_it++ == 0);
			Assert::IsTrue(*r_it++ == 1);
			Assert::AreEqual(unsigned(100), test.getSize());
		}

		TEST_METHOD(PublicQueue_TestIteratorPreDecrementOperator) {
			auto test = PublicQueue<int>();
			for (int x = 0; x < 100; x++) {
				test.push(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}

			auto r_it = test.end();
			for (int x = 99; x > 0; x--) {
				Assert::AreEqual(x - 1, *--r_it);
			}
			Assert::IsTrue(*--r_it == 99);
			Assert::IsTrue(*--r_it == 98);
			Assert::AreEqual(unsigned(100), test.getSize());
		}

		TEST_METHOD(PublicQueue_TestIteratorPostDecrementOperator) {
			auto test = PublicQueue<int>();
			for (int x = 0; x < 100; x++) {
				test.push(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}

			auto r_it = test.end();
			for (int x = 99; x >= 0; x--) {
				Assert::IsTrue(*r_it-- == x);
			}
			Assert::IsTrue(*r_it-- == 99);
			Assert::IsTrue(*r_it-- == 98);
			Assert::AreEqual(unsigned(100), test.getSize());
		}

		TEST_METHOD(PublicQueue_TestPartialIteratorConstructor) {
			auto test = PublicQueue<int>();
			for (int x = 0; x < 100; x++) {
				test.push(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}

			auto r_it = test.begin();
			for (int i = 0; i < 10; i++) { r_it++; };

			auto test2 = PublicQueue<int>(r_it, test.end());
			Assert::AreEqual(unsigned(90), test2.getSize());
			r_it = test2.begin();

			for (int x = 10; x < 100; x++) {
				int y = *r_it++;
				Assert::IsTrue(y == x);
			}
			Assert::IsTrue(*r_it++ == 10);
			Assert::IsTrue(*r_it++ == 11);
		}

		TEST_METHOD(PublicQueue_TestFullIteratorConstructor) {
			auto test = PublicQueue<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			for (int x = 0; x < 100; x++) {
				test.push(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}
			Assert::AreEqual(unsigned(100), test.getSize());
			auto r_it = test.begin();
			auto test2 = PublicQueue<int>(r_it, test.end());
			Assert::AreEqual(unsigned(100), test2.getSize());

			for (int x = 0; x < 100; x++) {
				int y = *r_it++;
				Assert::IsTrue(y == x);
			}
			Assert::IsTrue(*r_it++ == 0);
			Assert::IsTrue(*r_it++ == 1);
		}

		TEST_METHOD(PublicQueue_TestAssignmentOverload) {
			auto test = PublicQueue<int>(100, 4);
			auto test2 = PublicQueue<int>(1, 1);
			int y = -2;
			test.push(y);
			Assert::AreEqual(101U, test.getSize());
			test2 = test;
			Assert::AreEqual(101U, test.getSize());
			Assert::AreEqual(101U, test2.getSize());
			Assert::AreEqual(4, *test.begin());
			Assert::AreEqual(4, *test2.begin());
			Assert::AreEqual(-2, *test.end());
			Assert::AreEqual(-2, *test2.end());
		}
	};

	TEST_CLASS(QueueTests)
	{
	public:

		TEST_METHOD(Queue_TestEmptyConstructor)
		{
			Queue<int> test = Queue<int>();
			Assert::AreEqual(unsigned int(0), test.getSize());
			Assert::IsTrue(nullptr == test.head());
			Assert::IsTrue(nullptr == test.tail());
			Assert::IsTrue(test.empty());
		}

		TEST_METHOD(Queue_TestPushConnections)
		{
			Queue<int> test = Queue<int>();
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			auto x = 5;
			auto y = 0;
			test.push(x);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(1), test.getSize());
			test.push(y);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(2), test.getSize());

			Assert::IsTrue(test.head() == test.head()->next->prev);
			Assert::IsTrue(test.head() == test.head()->prev->next);
			Assert::IsTrue(test.tail() == test.tail()->next->prev);
			Assert::IsTrue(test.tail() == test.tail()->prev->next);
		}

		TEST_METHOD(Queue_TestOnePushItemQueue) {
			Queue<int> test = Queue<int>();
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			auto x = 5;
			auto y = 0;
			test.push(y);
			Assert::IsFalse(test.empty());

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

		TEST_METHOD(Queue_TestTwoPushItemQueue) {
			Queue<int> test = Queue<int>();
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			auto x = 5;
			auto y = 0;
			test.push(y);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(1), test.getSize());
			test.push(x);
			Assert::IsFalse(test.empty());
			// <-> 0 <-> 1 <->

			CDLL<int>::node * thisThing = test.head();

			Assert::AreEqual(unsigned int(2), test.getSize());

			Assert::AreEqual(y, test.head()->data);
			Assert::AreEqual(x, test.tail()->data);


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

		TEST_METHOD(Queue_TestThreePushItemQueue) {
			Queue<int> test = Queue<int>();
			auto x = 0;
			auto y = 1;
			auto z = 2;
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push(x);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(1), test.getSize());
			test.push(y);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(2), test.getSize());
			test.push(z);
			Assert::IsFalse(test.empty());
			// <-> 0 <-> 1 <-> 2 <->

			CDLL<int>::node * thisThing = test.head();

			Assert::AreEqual(unsigned int(3), test.getSize());

			Assert::AreEqual(x, test.head()->data);
			Assert::AreEqual(z, test.tail()->data);

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

		TEST_METHOD(Queue_TestPopEmptyQueue) {
			bool exceptionThrown = false;
			auto test = Queue<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			try {
				test.pop();
			}
			catch (runtime_error) {
				exceptionThrown = true;
			}
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(Queue_TestPopAfterPush) {
			auto test = Queue<int>();
			auto x = 1;
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			test.push(x);
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::AreEqual(1, test.pop());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(Queue_TestPopAfterTwoPush) {
			auto test = Queue<int>();
			auto x = 1;
			auto y = 2;
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			test.push(x);
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			test.push(y);
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::AreEqual(1, test.pop());
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::AreEqual(2, test.pop());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(Queue_TestPopFrontAfterThreePush) {
			auto test = Queue<int>();
			auto x = 1;
			auto y = 2;
			auto z = 3;
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			test.push(x);
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			test.push(y);
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			test.push(z);
			Assert::AreEqual(unsigned(3), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::AreEqual(1, test.pop());
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::AreEqual(2, test.pop());
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::AreEqual(3, test.pop());
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(Queue_TestReleaseAndDestructor) {
			auto test = Queue<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			for (int x = 0; x < 1000; x++) {
				test.push(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}
			Assert::IsTrue(test.getSize() == 1000);
			Assert::IsFalse(test.empty());
			test.release();
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
		}

		TEST_METHOD(Queue_TestCopyConstructorEmpty) {
			auto test = Queue<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			bool exceptionThrown = false;
			try {
				auto test2 = Queue<int>(test);
			}
			catch (...) {
				exceptionThrown = true;
			}
			Assert::IsFalse(exceptionThrown);
			Assert::AreEqual(unsigned(0), test.getSize());
		}

		TEST_METHOD(Queue_TestCopyConstructor) {
			auto test = Queue<int>();
			auto x = 4;
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push(x);
			Assert::AreEqual(unsigned(1), test.getSize());

			auto test2 = Queue<int>(test);
			Assert::AreEqual(unsigned(1), test2.getSize());
			Assert::IsFalse(&(test.head()->data) == &(test2.head()->data));
			Assert::IsTrue(test.head()->data == test2.head()->data);
		}

		TEST_METHOD(Queue_TestCopyObjectConstructor) {
			class Dummy {
			public:
				Dummy(int x) : m_x(x) {};
				int m_x = 0;
			};

			auto test = Queue<Dummy>();
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push(Dummy(5));
			Assert::AreEqual(unsigned(1), test.getSize());

			auto test2 = Queue<Dummy>(test);
			Assert::AreEqual(unsigned(1), test2.getSize());
			Assert::IsFalse(&(test.head()->data) == &(test2.head()->data));
			Assert::IsTrue(test.head()->data.m_x == test2.head()->data.m_x);
		}

		TEST_METHOD(Queue_TestIteratorPreIncrementOperator) {
			auto test = Queue<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			for (int x = 0; x < 100; x++) {
				test.push(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}

			auto r_it = test.begin();
			for (int x = 0; x < 99; x++) {
				Assert::IsTrue(*++r_it == x + 1);
			}
			Assert::IsTrue(*++r_it == 0);
			Assert::IsTrue(*++r_it == 1);
			Assert::AreEqual(unsigned(100), test.getSize());
		}

		TEST_METHOD(Queue_TestIteratorPostIncrementOperator) {
			auto test = Queue<int>();
			for (int x = 0; x < 100; x++) {
				test.push(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}

			auto r_it = test.begin();
			for (int x = 0; x < 100; x++) {
				Assert::IsTrue(*r_it++ == x);
			}
			Assert::IsTrue(*r_it++ == 0);
			Assert::IsTrue(*r_it++ == 1);
			Assert::AreEqual(unsigned(100), test.getSize());
		}

		TEST_METHOD(Queue_TestIteratorPreDecrementOperator) {
			auto test = Queue<int>();
			for (int x = 0; x < 100; x++) {
				test.push(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}

			auto r_it = test.end();
			for (int x = 99; x > 0; x--) {
				Assert::AreEqual(x - 1, *--r_it);
			}
			Assert::IsTrue(*--r_it == 99);
			Assert::IsTrue(*--r_it == 98);
			Assert::AreEqual(unsigned(100), test.getSize());
		}

		TEST_METHOD(Queue_TestIteratorPostDecrementOperator) {
			auto test = Queue<int>();
			for (int x = 0; x < 100; x++) {
				test.push(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}

			auto r_it = test.end();
			for (int x = 99; x >= 0; x--) {
				Assert::IsTrue(*r_it-- == x);
			}
			Assert::IsTrue(*r_it-- == 99);
			Assert::IsTrue(*r_it-- == 98);
			Assert::AreEqual(unsigned(100), test.getSize());
		}

		TEST_METHOD(Queue_TestPartialIteratorConstructor) {
			auto test = Queue<int>();
			for (int x = 0; x < 100; x++) {
				test.push(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}

			auto r_it = test.begin();
			for (int i = 0; i < 10; i++) { r_it++; };

			auto test2 = Queue<int>(r_it, test.end());
			Assert::AreEqual(unsigned(90), test2.getSize());
			r_it = test2.begin();

			for (int x = 10; x < 100; x++) {
				int y = *r_it++;
				Assert::IsTrue(y == x);
			}
			Assert::IsTrue(*r_it++ == 10);
			Assert::IsTrue(*r_it++ == 11);
		}

		TEST_METHOD(Queue_TestFullIteratorConstructor) {
			auto test = Queue<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			for (int x = 0; x < 100; x++) {
				test.push(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}
			Assert::AreEqual(unsigned(100), test.getSize());
			auto r_it = test.begin();
			auto test2 = Queue<int>(r_it, test.end());
			Assert::AreEqual(unsigned(100), test2.getSize());

			for (int x = 0; x < 100; x++) {
				int y = *r_it++;
				Assert::IsTrue(y == x);
			}
			Assert::IsTrue(*r_it++ == 0);
			Assert::IsTrue(*r_it++ == 1);
		}

		TEST_METHOD(Queue_TestAssignmentOverload) {
			auto test = Queue<int>(100, 4);
			auto test2 = Queue<int>(1, 1);
			int y = -2;
			test.push(y);
			Assert::AreEqual(101U, test.getSize());
			test2 = test;
			Assert::AreEqual(101U, test.getSize());
			Assert::AreEqual(101U, test2.getSize());
			Assert::AreEqual(4, *test.begin());
			Assert::AreEqual(4, *test2.begin());
			Assert::AreEqual(-2, *test.end());
			Assert::AreEqual(-2, *test2.end());
		}
	};

	TEST_CLASS(ListTests)
	{
	public:
		
		TEST_METHOD(TestEmptyConstructor)
		{
			CDLL<int> test = CDLL<int>();
			Assert::AreEqual(unsigned int(0), test.getSize());
			Assert::IsTrue(nullptr == test.head());
			Assert::IsTrue(nullptr == test.tail());
			Assert::IsTrue(test.empty());
		}

		TEST_METHOD(TestPushFrontConnections) 
		{
			CDLL<int> test = CDLL<int>();
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push_front(5);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(1), test.getSize());
			test.push_front(0);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(2), test.getSize());

			Assert::IsTrue(test.head() == test.head()->next->prev);
			Assert::IsTrue(test.head() == test.head()->prev->next);
			Assert::IsTrue(test.tail() == test.tail()->next->prev);
			Assert::IsTrue(test.tail() == test.tail()->prev->next);
		}

		TEST_METHOD(TestPushBackConnections)
		{
			CDLL<int> test = CDLL<int>();
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push_back(5);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(1), test.getSize());
			test.push_back(0);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(2), test.getSize());

			Assert::IsTrue(test.head() == test.head()->next->prev);
			Assert::IsTrue(test.head() == test.head()->prev->next);
			Assert::IsTrue(test.tail() == test.tail()->next->prev);
			Assert::IsTrue(test.tail() == test.tail()->prev->next);
		}

		TEST_METHOD(TestOnePushFrontItemList) {
			CDLL<int> test = CDLL<int>();
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push_front(0);
			Assert::IsFalse(test.empty());
			
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
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push_front(0);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(1), test.getSize());
			test.push_front(1);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(2), test.getSize());
			// <-> 1 <-> 0 <->

			CDLL<int>::node * thisThing = test.head();
			
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
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push_front(0);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(1), test.getSize());
			test.push_front(1);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(2), test.getSize());
			test.push_front(2);
			Assert::IsFalse(test.empty());
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
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push_back(0);
			Assert::IsFalse(test.empty());

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
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push_back(0);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(1), test.getSize());
			test.push_back(1);
			Assert::IsFalse(test.empty());
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
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push_back(0);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(1), test.getSize());
			test.push_back(1);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(2), test.getSize());
			test.push_back(2);
			Assert::IsFalse(test.empty());
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

		TEST_METHOD(TestPopFrontEmptyList) {
			bool exceptionThrown = false;
			auto test = CDLL<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			try {
				test.pop_front();
			}
			catch (runtime_error) {
				exceptionThrown = true;
			}
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(TestPopFrontAfterPushFront) {
			auto test = CDLL<int>();
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push_front(1);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::AreEqual(1, test.pop_front());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(TestPopFrontAfterTwoPushFront) {
			auto test = CDLL<int>();
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push_front(1);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(1), test.getSize());
			test.push_front(2);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::AreEqual(2, test.pop_front());
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::AreEqual(1, test.pop_front());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(TestPopFrontAfterThreePushFront) {
			auto test = CDLL<int>();
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push_front(1);
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			test.push_front(2);
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			test.push_front(3);
			Assert::AreEqual(unsigned(3), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::AreEqual(3, test.pop_front());
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::AreEqual(2, test.pop_front());
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::AreEqual(1, test.pop_front());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(TestPopFrontAfterPushBack) {
			auto test = CDLL<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			test.push_back(1);
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::AreEqual(1, test.pop_front());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(TestPopFrontAfterTwoPushBack) {
			auto test = CDLL<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			test.push_back(1);
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			test.push_back(2);
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::AreEqual(1, test.pop_front());
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::AreEqual(2, test.pop_front());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(TestPopFrontAfterThreePushBack) {
			auto test = CDLL<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			test.push_back(1);
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			test.push_back(2);
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			test.push_back(3);
			Assert::AreEqual(unsigned(3), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::AreEqual(1, test.pop_front());
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::AreEqual(2, test.pop_front());
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::AreEqual(3, test.pop_front());
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(TestPopFrontRandomPushSeries) {
			auto test = CDLL<int>();
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push_back(1);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(1), test.getSize());
			test.push_front(4);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(2), test.getSize());
			test.push_back(3);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(3), test.getSize());
			test.push_front(2);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(4), test.getSize());
			test.push_back(5);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(5), test.getSize());
			test.push_back(6);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(6), test.getSize());

			Assert::AreEqual(2, test.pop_front());
			Assert::AreEqual(unsigned(5), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::AreEqual(4, test.pop_front());
			Assert::AreEqual(unsigned(4), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::AreEqual(1, test.pop_front());
			Assert::AreEqual(unsigned(3), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::AreEqual(3, test.pop_front());
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::AreEqual(5, test.pop_front());
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::AreEqual(6, test.pop_front());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(TestPopBackEmptyList) {
			bool exceptionThrown = false;
			auto test = CDLL<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			try {
				test.pop_back();
			}
			catch (runtime_error) {
				exceptionThrown = true;
			}
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(TestPopBackAfterPushBack) {
			auto test = CDLL<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			test.push_back(1);
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::AreEqual(1, test.pop_back());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(TestPopBackAfterTwoPushBack) {
			auto test = CDLL<int>();
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push_back(1);
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			test.push_back(2);
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::AreEqual(2, test.pop_back());
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::AreEqual(1, test.pop_back());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(TestPopBackAfterThreePushBack) {
			auto test = CDLL<int>();
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push_back(1);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(1), test.getSize());
			test.push_back(2);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(2), test.getSize());
			test.push_back(3);
			Assert::IsFalse(test.empty());
			Assert::AreEqual(unsigned(3), test.getSize());
			Assert::AreEqual(3, test.pop_back());
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::AreEqual(2, test.pop_back());
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::AreEqual(1, test.pop_back());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(TestPopBackAfterPushFront) {
			auto test = CDLL<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			test.push_front(1);
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::AreEqual(1, test.pop_back());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(TestPopBackAfterTwoPushFront) {
			auto test = CDLL<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			test.push_front(1);
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			test.push_front(2);
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::AreEqual(1, test.pop_back());
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::AreEqual(2, test.pop_back());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(TestPopBackAfterThreePushFront) {
			auto test = CDLL<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			test.push_front(1);
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			test.push_front(2);
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			test.push_front(3);
			Assert::AreEqual(unsigned(3), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::AreEqual(1, test.pop_back());
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::AreEqual(2, test.pop_back());
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::AreEqual(3, test.pop_back());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(TestPopBackRandomPushSeries) {
			auto test = CDLL<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			test.push_back(1);
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			test.push_front(4);
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			test.push_back(3);
			Assert::AreEqual(unsigned(3), test.getSize());
			Assert::IsFalse(test.empty());
			test.push_front(2);
			Assert::AreEqual(unsigned(4), test.getSize());
			Assert::IsFalse(test.empty());
			test.push_back(5);
			Assert::AreEqual(unsigned(5), test.getSize());
			Assert::IsFalse(test.empty());
			test.push_back(6);
			Assert::AreEqual(unsigned(6), test.getSize());
			Assert::IsFalse(test.empty());
			
			Assert::AreEqual(6, test.pop_back());
			Assert::AreEqual(unsigned(5), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::AreEqual(5, test.pop_back());
			Assert::AreEqual(unsigned(4), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::AreEqual(3, test.pop_back());
			Assert::AreEqual(unsigned(3), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::AreEqual(1, test.pop_back());
			Assert::AreEqual(unsigned(2), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::AreEqual(4, test.pop_back());
			Assert::AreEqual(unsigned(1), test.getSize());
			Assert::IsFalse(test.empty());
			Assert::IsTrue(test.tail()->next->prev == test.tail());
			Assert::IsTrue(test.tail()->prev->next == test.tail());
			Assert::IsTrue(test.head()->next->prev == test.head());
			Assert::IsTrue(test.head()->prev->next == test.head());
			Assert::AreEqual(2, test.pop_back());
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
			Assert::IsTrue(test.head() == nullptr);
			Assert::IsTrue(test.tail() == nullptr);
		}

		TEST_METHOD(TestFrontAndBack) {
			auto test = CDLL<int>();
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			
			bool exceptionThrown = false;
			try { test.front(); }
			catch (runtime_error) { exceptionThrown = true; }
			Assert::IsTrue(exceptionThrown);
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());
			
			exceptionThrown = false;
			try { test.back(); }
			catch (runtime_error) { exceptionThrown = true; }
			Assert::IsTrue(exceptionThrown);
			Assert::IsTrue(test.empty());
			Assert::AreEqual(unsigned(0), test.getSize());

			test.push_back(1);
			Assert::IsFalse(test.empty());
			Assert::IsTrue(1 == test.front());
			Assert::IsTrue(1 == test.back());
			Assert::AreEqual(unsigned(1), test.getSize());
			test.push_front(4);
			Assert::IsFalse(test.empty());
			Assert::IsTrue(4 == test.front());
			Assert::IsTrue(1 == test.back());
			Assert::AreEqual(unsigned(2), test.getSize());
			test.push_back(3);
			Assert::IsFalse(test.empty());
			Assert::IsTrue(4 == test.front());
			Assert::IsTrue(3 == test.back());
			Assert::AreEqual(unsigned(3), test.getSize());
			test.push_front(2);
			Assert::IsFalse(test.empty());
			Assert::IsTrue(2 == test.front());
			Assert::IsTrue(3 == test.back());
			Assert::AreEqual(unsigned(4), test.getSize());
			test.push_back(5);
			Assert::IsFalse(test.empty());
			Assert::IsTrue(2 == test.front());
			Assert::IsTrue(5 == test.back());
			Assert::AreEqual(unsigned(5), test.getSize());
			test.push_back(6);
			Assert::IsFalse(test.empty());
			Assert::IsTrue(2 == test.front());
			Assert::IsTrue(6 == test.back());
			Assert::AreEqual(unsigned(6), test.getSize());
		}

		TEST_METHOD(TestReleaseAndDestructor) {
			auto test = CDLL<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			for (int x = 0; x < 1000; x++) {
				test.push_front(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}
			Assert::IsTrue(test.getSize() == 1000);
			Assert::IsFalse(test.empty());
			test.release();
			Assert::AreEqual(unsigned(0), test.getSize());
			Assert::IsTrue(test.empty());
		}

		TEST_METHOD(TestCopyConstructorEmpty) {
			auto test = CDLL<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			bool exceptionThrown = false;
			try {
				auto test2 = CDLL<int>(test);
			}
			catch (...) {
				exceptionThrown = true;
			}
			Assert::IsFalse(exceptionThrown);
			Assert::AreEqual(unsigned(0), test.getSize());
		}

		TEST_METHOD(TestCopyConstructor) {
			auto test = CDLL<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push_front(4);
			Assert::AreEqual(unsigned(1), test.getSize());
			
			auto test2 = CDLL<int>(test);
			Assert::AreEqual(unsigned(1), test2.getSize());
			Assert::IsFalse(&(test.head()->data) == &(test2.head()->data));
			Assert::IsTrue(test.head()->data == test2.head()->data);
		}

		TEST_METHOD(TestCopyObjectConstructor) {
			class Dummy {
			public:
				Dummy(int x) : m_x(x) {};
				int m_x = 0;
			};

			auto test = CDLL<Dummy>();
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push_front(Dummy(5));
			Assert::AreEqual(unsigned(1), test.getSize());

			auto test2 = CDLL<Dummy>(test);
			Assert::AreEqual(unsigned(1), test2.getSize());
			Assert::IsFalse(&(test.head()->data) == &(test2.head()->data));
			Assert::IsTrue(test.head()->data.m_x == test2.head()->data.m_x);
		}

		TEST_METHOD(TestIteratorPreIncrementOperator) {
			auto test = CDLL<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			for (int x = 0; x < 100; x++) {
				test.push_back(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}

			auto r_it = test.begin();
			for (int x = 0; x < 99; x++) {
				Assert::IsTrue(*++r_it == x + 1);
			}
			Assert::IsTrue(*++r_it == 0);
			Assert::IsTrue(*++r_it == 1);
			Assert::AreEqual(unsigned(100), test.getSize());
		}

		TEST_METHOD(TestIteratorPostIncrementOperator) {
			auto test = CDLL<int>();
			for (int x = 0; x < 100; x++) {
				test.push_back(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}

			auto r_it = test.begin();
			for (int x = 0; x < 100; x++) {
				Assert::IsTrue(*r_it++ == x);
			}
			Assert::IsTrue(*r_it++ == 0);
			Assert::IsTrue(*r_it++ == 1);
			Assert::AreEqual(unsigned(100), test.getSize());
		}

		TEST_METHOD(TestIteratorPreDecrementOperator) {
			auto test = CDLL<int>();
			for (int x = 0; x < 100; x++) {
				test.push_front(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}

			auto r_it = test.end();
			for (int x = 0; x < 99; x++) {
				Assert::IsTrue(*--r_it == x + 1);
			}
			Assert::IsTrue(*--r_it == 0);
			Assert::IsTrue(*--r_it == 1);
			Assert::AreEqual(unsigned(100), test.getSize());
		}

		TEST_METHOD(TestIteratorPostDecrementOperator) {
			auto test = CDLL<int>();
			for (int x = 0; x < 100; x++) {
				test.push_front(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}

			auto r_it = test.end();
			for (int x = 0; x < 100; x++) {
				Assert::IsTrue(*r_it-- == x);
			}
			Assert::IsTrue(*r_it-- == 0);
			Assert::IsTrue(*r_it-- == 1);
			Assert::AreEqual(unsigned(100), test.getSize());
		}

		TEST_METHOD(TestPartialIteratorConstructor) {
			auto test = CDLL<int>();
			for (int x = 0; x < 100; x++) {
				test.push_back(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}

			auto r_it = test.begin();
			for (int i = 0; i < 10; i++) { r_it++; };

			auto test2 = CDLL<int>(r_it, test.end());
			Assert::AreEqual(unsigned(90), test2.getSize());
			r_it = test2.begin();

			for (int x = 10; x < 100; x++) {
				int y = *r_it++;
				Assert::IsTrue(y == x);
			}
			Assert::IsTrue(*r_it++ == 10);
			Assert::IsTrue(*r_it++ == 11);
		}

		TEST_METHOD(TestFullIteratorConstructor) {
			auto test = CDLL<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			for (int x = 0; x < 100; x++) {
				test.push_back(x);
				Assert::AreEqual(unsigned(x + 1), test.getSize());
			}
			Assert::AreEqual(unsigned(100), test.getSize());
			auto r_it = test.begin();
			auto test2 = CDLL<int>(r_it, test.end());
			Assert::AreEqual(unsigned(100), test2.getSize());

			for (int x = 0; x < 100; x++) {
				int y = *r_it++;
				Assert::IsTrue(y == x);
			}
			Assert::IsTrue(*r_it++ == 0);
			Assert::IsTrue(*r_it++ == 1);
		}

		TEST_METHOD(TestCopyConstructorBiggerList) {
			auto test = CDLL<int>(100, 4);
			test.push_front(-1);
			test.push_back(-2);
			Assert::AreEqual(102U, test.getSize());
			auto test2 = test;
			Assert::AreEqual(102U, test.getSize());
			Assert::AreEqual(-1, *test.begin());
			Assert::AreEqual(-1, *test2.begin());
			Assert::AreEqual(-2, *test.end());
			Assert::AreEqual(-2, *test2.end());
		}

		TEST_METHOD(TestAssignmentOverload) {
			auto test = CDLL<int>(100, 4);
			auto test2 = CDLL<int>(1, 1);
			test.push_front(-1);
			test.push_back(-2);
			Assert::AreEqual(102U, test.getSize());
			test2 = test;
			Assert::AreEqual(102U, test.getSize());
			Assert::AreEqual(102U, test2.getSize());
			Assert::AreEqual(-1, *test.begin());
			Assert::AreEqual(-1, *test2.begin());
			Assert::AreEqual(-2, *test.end());
			Assert::AreEqual(-2, *test2.end());
		}
	};
}