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

		TEST_METHOD(MinutelyComparisonTests)
		{
			CTime early(0, 0, 0);
			CTime late(0, 0, 0);

			for (short earlyMinute = 0; earlyMinute < 60; earlyMinute++) {
				early.setMinute(earlyMinute);
				late.setMinute(earlyMinute);
				Assert::IsTrue(early == late);
				Assert::IsTrue(early <= late);
				Assert::IsTrue(late >= early);
				for (short lateMinute = earlyMinute + 1; lateMinute < 60; lateMinute++) {
					late.setMinute(lateMinute);
					Assert::IsTrue(early < late);
					Assert::IsTrue(late > early);
					Assert::IsTrue(early <= late);
					Assert::IsTrue(late >= early);
				}
			}
		}

		TEST_METHOD(HourlyAndMinutelyComparisonTests)
		{
			CTime time1(0, 0, 0);
			CTime time2(0, 0, 0);

			short defaultHour = 12;

			for (short hourVariation = -1; hourVariation <= 1; hourVariation++) {

				time1.setHour(defaultHour);
				time2.setHour(hourVariation + defaultHour);

				for (short earlyMinute = 0; earlyMinute < 60; earlyMinute++) {
					time1.setMinute(earlyMinute);
					time2.setMinute(earlyMinute);
					if (hourVariation == -1) {
						Assert::IsTrue(time1 > time2);
						Assert::IsTrue(time1 >= time2);
						Assert::IsTrue(time2 < time1);
						Assert::IsTrue(time2 <= time1);
					}
					else if (hourVariation == 0) {
						Assert::IsTrue(time1 == time2);
						Assert::IsTrue(time1 <= time2);
						Assert::IsTrue(time2 >= time1);
					}
					else {
						Assert::IsTrue(time2 > time1);
						Assert::IsTrue(time2 >= time1);
						Assert::IsTrue(time1 < time2);
						Assert::IsTrue(time1 <= time2);
					}
					
					for (short lateMinute = earlyMinute + 1; lateMinute < 60; lateMinute++) {
						time2.setMinute(lateMinute);

						if (hourVariation == -1) {
							Assert::IsTrue(time1 > time2);
							Assert::IsTrue(time1 >= time2);
							Assert::IsTrue(time2 < time1);
							Assert::IsTrue(time2 <= time1);
						}
						else if (hourVariation == 0) {
							Assert::IsTrue(time1 < time2);
							Assert::IsTrue(time2 > time1);
							Assert::IsTrue(time1 <= time2);
							Assert::IsTrue(time2 >= time1);
						}
						else {
							Assert::IsTrue(time2 > time1);
							Assert::IsTrue(time2 >= time1);
							Assert::IsTrue(time1 < time2);
							Assert::IsTrue(time1 <= time2);
						}
					}
				}

			}
		}

		TEST_METHOD(RandomSortTests) {
			auto time0 = CTime(13, 45, 23);
			auto time1 = CTime(10, 18, 53);
			auto time2 = CTime(17, 30, 38);
			auto time3 = CTime(5, 20, 15);
			auto time4 = CTime(10, 30, 50);
			auto time5 = CTime(15, 0, 18);
			auto time6 = CTime(13, 45, 23);

			Assert::IsTrue(time0 > time1);
			Assert::IsTrue(time1 < time2);
			Assert::IsTrue(time2 > time3);
			Assert::IsTrue(time3 < time4);
			Assert::IsTrue(time4 < time5);
			Assert::IsTrue(time5 > time6);
			Assert::IsTrue(time0 == time6);

			
		}

		TEST_METHOD(HourlyAndSecondlyComparisonTests)
		{
			CTime time1(0, 0, 0);
			CTime time2(0, 0, 0);

			short defaultMinute = 30;

			for (short minuteVariation = -1; minuteVariation <= 1; minuteVariation++) {

				time1.setMinute(defaultMinute);
				time2.setMinute(minuteVariation + defaultMinute);

				for (short earlySecond = 0; earlySecond < 60; earlySecond++) {
					time1.setSecond(earlySecond);
					time2.setSecond(earlySecond);
					if (minuteVariation == -1) {
						Assert::IsTrue(time1 > time2);
						Assert::IsTrue(time1 >= time2);
						Assert::IsTrue(time2 < time1);
						Assert::IsTrue(time2 <= time1);
					}
					else if (minuteVariation == 0) {
						Assert::IsTrue(time1 == time2);
						Assert::IsTrue(time1 <= time2);
						Assert::IsTrue(time2 >= time1);
					}
					else {
						Assert::IsTrue(time2 > time1);
						Assert::IsTrue(time2 >= time1);
						Assert::IsTrue(time1 < time2);
						Assert::IsTrue(time1 <= time2);
					}

					for (short lateSecond = earlySecond + 1; lateSecond < 60; lateSecond++) {
						time2.setSecond(lateSecond);

						if (minuteVariation == -1) {
							Assert::IsTrue(time1 > time2);
							Assert::IsTrue(time1 >= time2);
							Assert::IsTrue(time2 < time1);
							Assert::IsTrue(time2 <= time1);
						}
						else if (minuteVariation == 0) {
							Assert::IsTrue(time1 < time2);
							Assert::IsTrue(time2 > time1);
							Assert::IsTrue(time1 <= time2);
							Assert::IsTrue(time2 >= time1);
						}
						else {
							Assert::IsTrue(time2 > time1);
							Assert::IsTrue(time2 >= time1);
							Assert::IsTrue(time1 < time2);
							Assert::IsTrue(time1 <= time2);
						}
					}
				}
			}
		}

		TEST_METHOD(sortTest) {

		}

	private:
		void validateTime(CTime time) {
			Assert::IsTrue(time.getHour() >= 0 && time.getHour() < 24);
			Assert::IsTrue(time.getMinute() >= 0 && time.getMinute() < 60);
			Assert::IsTrue(time.getSecond() >= 0 && time.getSecond() < 60);
		}
		
	};
}