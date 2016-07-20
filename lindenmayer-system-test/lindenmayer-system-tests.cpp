#include "stdafx.h"
#include "CppUnitTest.h"

#include "../lindenmayer-system/lindenmayer-system.h"
#include "../lindenmayer-system/production-rule-builder.h"

#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lindenmayersystemtest {
	TEST_CLASS(LindenmayerSystemTests) {
	public:
		TEST_METHOD(NoRules) {
			LindenmayerString axiom;
			axiom.Add(LindenmayerSymbol('A', {}));
			axiom.Add(LindenmayerSymbol('B', {}));

			LindenmayerSystem system(axiom, {});

			LindenmayerString result = system.Run(1);

			Assert::AreEqual((size_t)2, result.Size());
			Assert::AreEqual('A', (*result[0]).GetSymbol());
			Assert::AreEqual('B', (*result[1]).GetSymbol());
		}

		TEST_METHOD(SingleIteration) {
			LindenmayerString axiom;
			axiom.Add(LindenmayerSymbol('A', {}));

			ProductionRuleBuilder ruleBuilder;
			std::vector<ProductionRule> rules;
			rules.push_back(std::move(ruleBuilder.Build(std::string(""), std::string(""), 'A', std::string("A()-A()"))));

			LindenmayerSystem system(axiom, std::move(rules));

			LindenmayerString result = system.Run(1);

			Assert::AreEqual((size_t)2, result.Size());
			Assert::AreEqual('A', result[0]->GetSymbol());
			Assert::AreEqual('A', result[1]->GetSymbol());
		}

		TEST_METHOD(TwoIterations) {

			LindenmayerString axiom;
			axiom.Add(LindenmayerSymbol('A', {}));

			ProductionRuleBuilder ruleBuilder;
			std::vector<ProductionRule> rules;
			rules.push_back(std::move(ruleBuilder.Build(std::string(""), std::string(""), 'A', std::string("A()-A()"))));

			LindenmayerSystem system(axiom, std::move(rules));

			LindenmayerString result = system.Run(2);

			Assert::AreEqual((size_t)4, result.Size());
			Assert::AreEqual('A', result[0]->GetSymbol());
			Assert::AreEqual('A', result[1]->GetSymbol());
			Assert::AreEqual('A', result[2]->GetSymbol());
			Assert::AreEqual('A', result[3]->GetSymbol());
		}

		TEST_METHOD(TwoIterationsWithTwoRules) {

			LindenmayerString axiom;
			axiom.Add(LindenmayerSymbol('A'));
			axiom.Add(LindenmayerSymbol('B'));

			ProductionRuleBuilder ruleBuilder;
			std::vector<ProductionRule> rules;
			rules.push_back(std::move(ruleBuilder.Build(std::string(""), std::string(""), 'A', std::string("A()-B()"))));
			rules.push_back(std::move(ruleBuilder.Build(std::string(""), std::string(""), 'B', std::string("B()"))));

			LindenmayerSystem system(axiom, std::move(rules));

			LindenmayerString result = system.Run(2);

			Assert::AreEqual((size_t)4, result.Size());
			Assert::AreEqual('A', result[0]->GetSymbol());
			Assert::AreEqual('B', result[1]->GetSymbol());
			Assert::AreEqual('B', result[2]->GetSymbol());
			Assert::AreEqual('B', result[3]->GetSymbol());
		}

		TEST_METHOD(WithContext) {
			LindenmayerString axiom;
			axiom.Add(LindenmayerSymbol('A'));

			ProductionRuleBuilder ruleBuilder;
			std::vector<ProductionRule> rules;
			rules.push_back(std::move(ruleBuilder.Build(std::string(""), std::string("B()"), 'A', std::string("C()"))));
			rules.push_back(std::move(ruleBuilder.Build(std::string(""), std::string(""), 'A', std::string("A()-B()"))));
			rules.push_back(std::move(ruleBuilder.Build(std::string(""), std::string(""), 'B', std::string("B()"))));

			LindenmayerSystem system(axiom, std::move(rules));

			LindenmayerString result = system.Run(1);

			Assert::AreEqual((size_t)2, result.Size());
			Assert::AreEqual('A', result[0]->GetSymbol());
			Assert::AreEqual('B', result[1]->GetSymbol());
		}

		TEST_METHOD(Test1) {
			LindenmayerString axiom;
			axiom.Add(LindenmayerSymbol('A', { 2.0f }));

			ProductionRuleBuilder ruleBuilder;
			std::vector<ProductionRule> rules;
			rules.push_back(std::move(ruleBuilder.Build(std::string(""), std::string(""), 'A', std::string("A(2 * a)"))));

			LindenmayerSystem system(axiom, std::move(rules));

			LindenmayerString result = system.Run(1);

			Assert::AreEqual((size_t)1, result.Size());
			Assert::AreEqual('A', result[0]->GetSymbol());
			Assert::AreEqual(4.0f, result[0]->GetParameters()[0]);
		}
	};
}