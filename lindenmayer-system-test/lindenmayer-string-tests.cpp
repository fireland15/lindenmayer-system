#include "stdafx.h"
#include "CppUnitTest.h"

#include "../lindenmayer-system/lindenmayer-string.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lindenmayersystemtest {
	TEST_CLASS(LindenmayerStringTests) {
	public:
		TEST_METHOD(CompareRangeBiggerThanString) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol());
			str.Add(LindenmayerSymbol());
			str.Add(LindenmayerSymbol());
			
			LindenmayerString compare;
			compare.Add(LindenmayerSymbol());
			compare.Add(LindenmayerSymbol());
			compare.Add(LindenmayerSymbol());
			compare.Add(LindenmayerSymbol());
			compare.Add(LindenmayerSymbol());

			bool result = str.CompareAhead(0, compare);

			Assert::AreEqual(false, result);
		}

		TEST_METHOD(CompareRangeAtPosition1) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol());
			str.Add(LindenmayerSymbol());
			str.Add(LindenmayerSymbol());

			LindenmayerString compare;
			compare.Add(LindenmayerSymbol());
			compare.Add(LindenmayerSymbol());
			compare.Add(LindenmayerSymbol());

			bool result = str.CompareAhead(1, compare);

			Assert::AreEqual(false, result);
		}

		TEST_METHOD(CompareRangeAtPosition2) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));

			LindenmayerString compare;
			compare.Add(LindenmayerSymbol('b'));

			bool result = str.CompareAhead(1, compare);

			Assert::AreEqual(true, result);
		}

		TEST_METHOD(CompareRangeAtPosition3) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));

			LindenmayerString compare;
			compare.Add(LindenmayerSymbol('b'));
			compare.Add(LindenmayerSymbol('c'));

			bool result = str.CompareAhead(1, compare);

			Assert::AreEqual(true, result);
		}

		TEST_METHOD(CompareRangeAtPosition4) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));

			LindenmayerString compare;
			compare.Add(LindenmayerSymbol('b'));
			compare.Add(LindenmayerSymbol('c'));
			compare.Add(LindenmayerSymbol('d'));

			bool result = str.CompareAhead(1, compare);

			Assert::AreEqual(false, result);
		}

		TEST_METHOD(CompareRangeAtPosition5) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));

			LindenmayerString compare;
			compare.Add(LindenmayerSymbol('g'));
			compare.Add(LindenmayerSymbol('d'));

			bool result = str.CompareAhead(0, compare);

			Assert::AreEqual(false, result);
		}

		TEST_METHOD(CompareRangePosBiggerThanSize) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol());
			str.Add(LindenmayerSymbol());
			str.Add(LindenmayerSymbol());

			LindenmayerString compare;
			compare.Add(LindenmayerSymbol());
			compare.Add(LindenmayerSymbol());

			bool result = str.CompareAhead(3, compare);

			Assert::AreEqual(false, result);
		}

		TEST_METHOD(CompareRangeOfZeroSize) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol());
			str.Add(LindenmayerSymbol());
			str.Add(LindenmayerSymbol());

			LindenmayerString compare;

			bool result = str.CompareAhead(1, compare);

			Assert::AreEqual(true, result);
		}

		TEST_METHOD(CompareBehindPosOutOfRange) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));
			str.Add(LindenmayerSymbol('d'));
			str.Add(LindenmayerSymbol('e'));
			str.Add(LindenmayerSymbol('f'));

			LindenmayerString compare;

			bool result = str.CompareBehind(7, compare);

			Assert::AreEqual(false, result);
		}

		TEST_METHOD(CompareBehindEmptyCompare) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));
			str.Add(LindenmayerSymbol('d'));
			str.Add(LindenmayerSymbol('e'));
			str.Add(LindenmayerSymbol('f'));

			LindenmayerString compare;

			bool result = str.CompareBehind(0, compare);

			Assert::AreEqual(true, result);
		}

		TEST_METHOD(CompareBehindNoRoomForFullCompare) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));
			str.Add(LindenmayerSymbol('d'));
			str.Add(LindenmayerSymbol('e'));
			str.Add(LindenmayerSymbol('f'));

			LindenmayerString compare;
			compare.Add(LindenmayerSymbol('a'));
			compare.Add(LindenmayerSymbol('b'));
			compare.Add(LindenmayerSymbol('c'));
			compare.Add(LindenmayerSymbol('d'));

			bool result = str.CompareBehind(2, compare);

			Assert::AreEqual(false, result);
		}

		TEST_METHOD(CompareBehindMatch1) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));
			str.Add(LindenmayerSymbol('d'));
			str.Add(LindenmayerSymbol('e'));
			str.Add(LindenmayerSymbol('f'));

			LindenmayerString compare;
			compare.Add(LindenmayerSymbol('a'));
			compare.Add(LindenmayerSymbol('b'));
			compare.Add(LindenmayerSymbol('c'));
			compare.Add(LindenmayerSymbol('d'));

			bool result = str.CompareBehind(3, compare);

			Assert::AreEqual(true, result);
		}

		TEST_METHOD(CompareBehindMatch2) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));
			str.Add(LindenmayerSymbol('d'));
			str.Add(LindenmayerSymbol('e'));
			str.Add(LindenmayerSymbol('f'));

			LindenmayerString compare;
			compare.Add(LindenmayerSymbol('c'));
			compare.Add(LindenmayerSymbol('d'));
			compare.Add(LindenmayerSymbol('e'));

			bool result = str.CompareBehind(4, compare);

			Assert::AreEqual(true, result);
		}

		TEST_METHOD(CompareBehindNoMatch) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));
			str.Add(LindenmayerSymbol('d'));
			str.Add(LindenmayerSymbol('e'));
			str.Add(LindenmayerSymbol('f'));

			LindenmayerString compare;
			compare.Add(LindenmayerSymbol('c'));
			compare.Add(LindenmayerSymbol('t'));
			compare.Add(LindenmayerSymbol('f'));

			bool result = str.CompareBehind(4, compare);

			Assert::AreEqual(false, result);
		}
	};
}