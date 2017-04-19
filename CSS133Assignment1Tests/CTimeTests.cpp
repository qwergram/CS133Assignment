#include "stdafx.h"
#include "CppUnitTest.h"


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
			validateTime(CTime());
		}

		TEST_METHOD(MaxHourConstructorTest)
		{
			CTime time = CTime(23);
			validateTime(time);
			Assert::AreEqual(time.getHour(), (short)23);
		}

		TEST_METHOD(OverflowMaxHourConstructorTest)
		{
			CTime time = CTime(24);
			validateTime(time);
			Assert::AreNotEqual(time.getHour(), (short)24);
		}

		TEST_METHOD(MaxMinuteConstructorTest)
		{
			CTime time = CTime(1, 59);
			validateTime(time);
			Assert::AreEqual(time.getHour(), (short)1);
			Assert::AreEqual(time.getMinute(), (short)59);
		}

		TEST_METHOD(OverflowMaxMinuteConstructorTest)
		{
			CTime time = CTime(1, 60);
			validateTime(time);
			Assert::AreEqual(time.getHour(), (short)1);
			Assert::AreNotEqual(time.getMinute(), (short)60);
		}

		TEST_METHOD(MaxSecondConstructorTest)
		{
			CTime time = CTime(1, 1, 59);
			validateTime(time);
			Assert::AreEqual(time.getHour(), (short)1);
			Assert::AreEqual(time.getMinute(), (short)1);
			Assert::AreEqual(time.getSecond(), (short)59);
		}

		TEST_METHOD(OverflowMaxSecondConstructorTest)
		{
			CTime time = CTime(1, 1, 60);
			validateTime(time);
			Assert::AreEqual(time.getHour(), (short)1);
			Assert::AreEqual(time.getMinute(), (short)1);
			Assert::AreNotEqual(time.getSecond(), (short)60);
		}

		// Hour Mutator/Accessor Tests

		TEST_METHOD(SetHourValidValues)
		{
			CTime time = CTime(0,0,0);
			for (short hour = 0; hour < 24; hour++) {
				time.setHour(hour);
				validateTime(time);
				Assert::AreEqual(time.getHour(), hour);
			}
		}

		TEST_METHOD(SetHourInValidValues)
		{
			CTime time = CTime(0, 0, 0);
			for (short hour = 24; hour < 100; hour++) {
				time.setHour(hour);
				validateTime(time);
				Assert::AreEqual(time.getHour(), (short)0);
			}
		}

		// Minute Mutator/Accessor Tests

		TEST_METHOD(SetMinuteValidValues)
		{
			CTime time = CTime(0, 0, 0);
			for (short minute = 0; minute < 60; minute++) {
				time.setMinute(minute);
				validateTime(time);
				Assert::AreEqual(time.getMinute(), minute);
			}
		}

		TEST_METHOD(SetMinuteInValidValues)
		{
			CTime time = CTime(0, 0, 0);
			for (short minute = 60; minute < 100; minute++) {
				time.setMinute(minute);
				validateTime(time);
				Assert::AreEqual(time.getMinute(), (short)0);
			}
		}

		// Second Mutator/Accessor Tests

		TEST_METHOD(SetSecondValidValues)
		{
			CTime time = CTime(0, 0, 0);
			for (short second = 0; second < 60; second++) {
				time.setSecond(second);
				validateTime(time);
				Assert::AreEqual(time.getSecond(), second);
			}
		}

		TEST_METHOD(SetSecondInValidValues)
		{
			CTime time = CTime(0, 0, 0);
			for (short second = 60; second < 100; second++) {
				time.setSecond(second);
				validateTime(time);
				Assert::AreEqual(time.getSecond(), (short)0);
			}
		}

		// Comparison Tests

		TEST_METHOD(HourlyComparisonTests) 
		{
			CTime early;
			CTime late;
			
			for (short earlyHour = 0; earlyHour < 24; earlyHour++) {
				early.setHour(earlyHour);
				late.setHour(earlyHour);
				Assert::IsTrue(early == late);
				Assert::IsTrue(early <= late);
				Assert::IsTrue(late >= early);
				for (short lateHour = earlyHour + 1; lateHour < 24; lateHour++) {
					late.setHour(lateHour);
					Assert::IsTrue(early < late);
					Assert::IsTrue(late > early);
					Assert::IsTrue(early <= late);
					Assert::IsTrue(late >= early);
				}
			}
		}

	private:
		void validateTime(CTime time) {
			Assert::IsTrue(time.getHour() >= 0 && time.getHour() < 24);
			Assert::IsTrue(time.getMinute() >= 0 && time.getMinute() < 60);
			Assert::IsTrue(time.getSecond() >= 0 && time.getSecond() < 60);
		}
		
	};
}