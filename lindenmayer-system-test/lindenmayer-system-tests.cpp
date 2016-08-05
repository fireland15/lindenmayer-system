#include "stdafx.h"
#include "CppUnitTest.h"

#include <vector>

#include "../lindenmayer-system/lindenmayer-system.h"
#include "../lindenmayer-system/factories.h"


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

			std::vector<ProductionRule> rules;
			rules.push_back(std::move(CreateProductionRule(std::string("A : A()-A()"))));

			LindenmayerSystem system(axiom, std::move(rules));

			LindenmayerString result = system.Run(1);

			Assert::AreEqual((size_t)2, result.Size());
			Assert::AreEqual('A', result[0]->GetSymbol());
			Assert::AreEqual('A', result[1]->GetSymbol());
		}

		TEST_METHOD(TwoIterations) {

			LindenmayerString axiom;
			axiom.Add(LindenmayerSymbol('A', {}));

			std::vector<ProductionRule> rules;
			rules.push_back(std::move(CreateProductionRule(std::string("A : A()-A()"))));

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

			std::vector<ProductionRule> rules;
			rules.push_back(std::move(CreateProductionRule(std::string("A : A()-B()"))));
			rules.push_back(std::move(CreateProductionRule(std::string("B : B()"))));

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

			std::vector<ProductionRule> rules;
			rules.push_back(std::move(CreateProductionRule(std::string("A > B: C()"))));
			rules.push_back(std::move(CreateProductionRule(std::string("A : A()-B()"))));
			rules.push_back(std::move(CreateProductionRule(std::string("A : B()"))));

			LindenmayerSystem system(axiom, std::move(rules));

			LindenmayerString result = system.Run(1);

			Assert::AreEqual((size_t)2, result.Size());
			Assert::AreEqual('A', result[0]->GetSymbol());
			Assert::AreEqual('B', result[1]->GetSymbol());
		}

		TEST_METHOD(Test1) {
			LindenmayerString axiom;
			axiom.Add(LindenmayerSymbol('A', { 2.0f }));

			std::vector<ProductionRule> rules;
			rules.push_back(std::move(CreateProductionRule(std::string("A : A(2 * a)"))));

			LindenmayerSystem system(axiom, std::move(rules));

			LindenmayerString result = system.Run(1);

			Assert::AreEqual((size_t)1, result.Size());
			Assert::AreEqual('A', result[0]->GetSymbol());
			Assert::AreEqual(4.0f, result[0]->GetParameters()[0]);
		}

		TEST_METHOD(Test2) {
			LindenmayerString axiom;
			axiom.Add(LindenmayerSymbol('A', { 2.0f }));

			std::vector<ProductionRule> rules;
			rules.push_back(std::move(CreateProductionRule(std::string("A < A : A(0)"))));
			rules.push_back(std::move(CreateProductionRule(std::string("A : A(2 * a)-A(2 * a)"))));

			LindenmayerSystem system(axiom, std::move(rules));

			LindenmayerString result = system.Run(2);

			Assert::AreEqual((size_t)3, result.Size());
			Assert::AreEqual('A', result[0]->GetSymbol());
			Assert::AreEqual(8.0f, result[0]->GetParameters()[0]);
			Assert::AreEqual('A', result[1]->GetSymbol());
			Assert::AreEqual(8.0f, result[1]->GetParameters()[0]);
			Assert::AreEqual('A', result[2]->GetSymbol());
			Assert::AreEqual(0.0f, result[2]->GetParameters()[0]);
		}
	};
}