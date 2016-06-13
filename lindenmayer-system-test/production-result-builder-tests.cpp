#include "stdafx.h"
#include "CppUnitTest.h"

#include "../expression-evaluator/expression-builder.h"
#include "../lindenmayer-system/lindenmayer-symbol-builder.h"
#include "../lindenmayer-system/lindenmayer-production-result-builder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lindenmayersystemtest {
	TEST_CLASS(ProductionResultGeneratorTests) {
	public:
		TEST_METHOD(ZeroSymbolsBuild) {
			LindenmayerSymbol symbol;
			symbol.symbol = 'a';
			symbol.parameters = { 3.0f, 5.0f };

			ProductionResultGenerator generator({});

			std::vector<LindenmayerSymbol> result = generator.Generate(symbol);

			Assert::AreEqual((size_t)0, result.size());
		}

		TEST_METHOD(SingleSymbolBuild) {
			LindenmayerSymbol symbol;
			symbol.symbol = 'b';
			symbol.parameters = { 3.0f, 6.0f };

			LindenmayerSymbolBuilder builder('v');

			ProductionResultGenerator generator({ builder });

			std::vector<LindenmayerSymbol> result = generator.Generate(symbol);

			Assert::AreEqual((size_t)1, result.size());
			Assert::AreEqual('v', result[0].symbol);
		}

		TEST_METHOD(TwoSymbolBuild) {
			LindenmayerSymbol symbol;
			symbol.symbol = 'b';
			symbol.parameters = { 3.0f, 6.0f };

			LindenmayerSymbolBuilder builder1('v');
			LindenmayerSymbolBuilder builder2('t');

			ProductionResultGenerator generator({ builder1, builder2 });

			std::vector<LindenmayerSymbol> result = generator.Generate(symbol);

			Assert::AreEqual((size_t)2, result.size());
			Assert::AreEqual('v', result[0].symbol);
			Assert::AreEqual('t', result[1].symbol);
		}

		TEST_METHOD(ThreeSymbolBuild) {
			LindenmayerSymbol symbol;
			symbol.symbol = 'b';
			symbol.parameters = { 3.0f, 6.0f };

			LindenmayerSymbolBuilder builder1('v');
			LindenmayerSymbolBuilder builder2('t');
			LindenmayerSymbolBuilder builder3('g');

			ProductionResultGenerator generator({ builder1, builder2, builder3 });

			std::vector<LindenmayerSymbol> result = generator.Generate(symbol);

			Assert::AreEqual((size_t)3, result.size());
			Assert::AreEqual('v', result[0].symbol);
			Assert::AreEqual('t', result[1].symbol);
			Assert::AreEqual('g', result[2].symbol);
		}

		TEST_METHOD(BuildSymbolWithOneParameter) {
			LindenmayerSymbol symbol;
			symbol.symbol = 'b';
			symbol.parameters = { 3.0f, 6.0f };

			ExpressionBuilder expBldr;
			Expression exp = expBldr.Build("a + b");

			LindenmayerSymbolBuilder builder('v', { exp });

			ProductionResultGenerator generator({ builder });

			std::vector<LindenmayerSymbol> result = generator.Generate(symbol);

			Assert::AreEqual((size_t)1, result.size());
			Assert::AreEqual('v', result[0].symbol);
			Assert::AreEqual((size_t)1, result[0].parameters.size());
			Assert::AreEqual(9.0f, result[0].parameters[0]);
		}

		TEST_METHOD(BuildSymbolWithTwoParameters) {
			LindenmayerSymbol symbol;
			symbol.symbol = 'b';
			symbol.parameters = { 3.0f, 6.0f };

			ExpressionBuilder expBldr;
			Expression exp1 = expBldr.Build("a + b");
			Expression exp2 = expBldr.Build("3 * a");

			LindenmayerSymbolBuilder builder('v', { exp1, exp2 });

			ProductionResultGenerator generator({ builder });

			std::vector<LindenmayerSymbol> result = generator.Generate(symbol);

			Assert::AreEqual((size_t)1, result.size());
			Assert::AreEqual('v', result[0].symbol);
			Assert::AreEqual((size_t)2, result[0].parameters.size());
			Assert::AreEqual(9.0f, result[0].parameters[0]);
			Assert::AreEqual(9.0f, result[0].parameters[1]);
		}

		TEST_METHOD(BuildSymbolWithThreeParameters) {
			LindenmayerSymbol symbol;
			symbol.symbol = 'b';
			symbol.parameters = { 3.0f, 6.0f };

			ExpressionBuilder expBldr;
			Expression exp1 = expBldr.Build("a + b");
			Expression exp2 = expBldr.Build("3 * a");
			Expression exp3 = expBldr.Build("12 / b");

			LindenmayerSymbolBuilder builder('v', { exp1, exp2, exp3 });

			ProductionResultGenerator generator({ builder });

			std::vector<LindenmayerSymbol> result = generator.Generate(symbol);

			Assert::AreEqual((size_t)1, result.size());
			Assert::AreEqual('v', result[0].symbol);
			Assert::AreEqual((size_t)3, result[0].parameters.size());
			Assert::AreEqual(9.0f, result[0].parameters[0]);
			Assert::AreEqual(9.0f, result[0].parameters[1]);
			Assert::AreEqual(2.0f, result[0].parameters[2]);
		}
	};
}