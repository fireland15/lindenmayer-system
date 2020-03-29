#include "stdafx.h"
#include "CppUnitTest.h"

#include "../lindenmayer-system/factories.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lindenmayersystemtest {
	TEST_CLASS(ProductionRuleBuilderTests) {
	public:
		TEST_METHOD(NoContext) {
			ProductionRule rule = CreateProductionRule(std::string("A : A()"));

			LindenmayerString lStr;
			lStr.Add(LindenmayerSymbol('C'));
			lStr.Add(LindenmayerSymbol('A'));
			lStr.Add(LindenmayerSymbol('D'));

			Assert::IsTrue(rule.CanReplace(lStr[1]));
			LindenmayerString result = rule.Produce(*(lStr[1]));
			Assert::AreEqual((size_t)1, result.Size());
			Assert::AreEqual('A', (*result[0]).GetSymbol());
		}

		TEST_METHOD(PreContext) {
			ProductionRule rule = CreateProductionRule(std::string("C < A : A()"));

			LindenmayerString lStr;
			lStr.Add(LindenmayerSymbol('C'));
			lStr.Add(LindenmayerSymbol('A'));
			lStr.Add(LindenmayerSymbol('D'));

			Assert::IsTrue(rule.CanReplace(lStr[1]));
		}

		TEST_METHOD(PostContext) {
			ProductionRule rule = CreateProductionRule(std::string("A > D : A()"));

			LindenmayerString lStr;
			lStr.Add(LindenmayerSymbol('C'));
			lStr.Add(LindenmayerSymbol('A'));
			lStr.Add(LindenmayerSymbol('D'));

			Assert::IsTrue(rule.CanReplace(lStr[1]));
		}

		TEST_METHOD(BothContext) {
			ProductionRule rule = CreateProductionRule(std::string("C < A > D : A()"));

			LindenmayerString lStr;
			lStr.Add(LindenmayerSymbol('C'));
			lStr.Add(LindenmayerSymbol('A'));
			lStr.Add(LindenmayerSymbol('D'));

			Assert::IsTrue(rule.CanReplace(lStr[1]));
		}
	};
}