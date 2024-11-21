#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab11.3/Lab11.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			int day, month, year;
			string dateStr = "01.10.2020";
			bool result = parseDate(dateStr, day, month, year);
			Assert::IsTrue(result);
			Assert::AreEqual(1, day);
			Assert::AreEqual(10, month);
			Assert::AreEqual(2020, year);
		}
	};
}
