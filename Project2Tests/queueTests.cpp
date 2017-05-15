#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Project2\queue.h"
#include "..\Project2\queue.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NP_ADT;

namespace Project2Tests
{
	TEST_CLASS(QueueTests)
	{
	public:

		TEST_METHOD(TestEmptyConstructor)
		{
			Queue<int> test = Queue<int>();
			Assert::AreEqual(unsigned int(0), test.getSize());
			Assert::IsTrue(nullptr == test.head());
			Assert::IsTrue(nullptr == test.tail());
			Assert::IsTrue(test.empty());
		}

		TEST_METHOD(TestCopyConstructorEmpty) {
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

		TEST_METHOD(TestCopyConstructor) {
			auto test = Queue<int>();
			Assert::AreEqual(unsigned(0), test.getSize());
			test.push(4);
			Assert::AreEqual(unsigned(1), test.getSize());

			auto test2 = Queue<int>(test);
			Assert::AreEqual(unsigned(1), test2.getSize());
			Assert::IsFalse(&(test.head()->data) == &(test2.head()->data));
			Assert::IsTrue(test.head()->data == test2.head()->data);
		}

		TEST_METHOD(TestCopyObjectConstructor) {
			class Dummy;
			class Dummy {
			public:
				Dummy(int x) : m_x(x) {};
				int m_x = 0;
			};
			
			// auto test = Queue<Dummy>();
			//Assert::AreEqual(unsigned(0), test.getSize());
			//test.push(Dummy(5));
			//Assert::AreEqual(unsigned(1), test.getSize());

			//auto test2 = Queue<Dummy>(test);
			//Assert::AreEqual(unsigned(1), test2.getSize());
			//Assert::IsFalse(&(test.head()->data) == &(test2.head()->data));
			//Assert::IsTrue(test.head()->data.m_x == test2.head()->data.m_x);
		}

	};
}