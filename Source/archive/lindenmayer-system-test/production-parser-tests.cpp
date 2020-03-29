#include "stdafx.h"
#include "CppUnitTest.h"

#include "../lindenmayer-system/production-parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lindenmayersystemtest {
	TEST_CLASS(ProductionStringParserTests) {
	public:
		TEST_METHOD(test1) {
			ProductionStringParser parser(std::string("a < x > c : abc"));

			Assert::AreEqual(std::string("a"), parser.GetPreContext());
			Assert::AreEqual('x', parser.GetSymbol());
			Assert::AreEqual(std::string("c"), parser.GetPostContext());
			Assert::AreEqual(std::string("abc"), parser.GetResult());
		}

		TEST_METHOD(test2) {
			ProductionStringParser parser(std::string("a < x(a,b) > c : a(a,b)b()c(b)"));

			Assert::AreEqual(std::string("a"), parser.GetPreContext());
			Assert::AreEqual('x', parser.GetSymbol());
			Assert::AreEqual(std::string("c"), parser.GetPostContext());
			Assert::AreEqual(std::string("a(a,b)b()c(b)"), parser.GetResult());
		}
	};
}