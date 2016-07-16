#include "stdafx.h"
#include "CppUnitTest.h"

#include "../expression-evaluator/expression-builder.h"
#include "../lindenmayer-system/lindenmayer-symbol-builder.h"
#include "../lindenmayer-system/production-result-generator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lindenmayersystemtest {
	TEST_CLASS(ProductionResultGeneratorTests) {
	public:
		TEST_METHOD(ZeroSymbolsBuild) {
			LindenmayerSymbol symbol;
			symbol.SetSymbol('b');
			symbol.SetParameters({ 3.0f, 6.0f });

			ProductionResultGenerator generator({});

			LindenmayerString result = generator.Generate(symbol);

			Assert::AreEqual((size_t)0, result.Size());
		}

		TEST_METHOD(SingleSymbolBuild) {
			LindenmayerSymbol symbol;
			symbol.SetSymbol('b');
			symbol.SetParameters({ 3.0f, 6.0f });

			LindenmayerSymbolBuilder builder('v');

			ProductionResultGenerator generator({ builder });

			LindenmayerString result = generator.Generate(symbol);

			Assert::AreEqual((size_t)1, result.Size());
			Assert::AreEqual('v', (*result[0]).GetSymbol());
		}

		TEST_METHOD(TwoSymbolBuild) {
			LindenmayerSymbol symbol;
			symbol.SetSymbol('b');
			symbol.SetParameters({ 3.0f, 6.0f });

			LindenmayerSymbolBuilder builder1('v');
			LindenmayerSymbolBuilder builder2('t');

			ProductionResultGenerator generator({ builder1, builder2 });

			LindenmayerString result = generator.Generate(symbol);

			Assert::AreEqual((size_t)2, result.Size());
			Assert::AreEqual('v', (*result[0]).GetSymbol());
			Assert::AreEqual('t', (*result[1]).GetSymbol());
		}

		TEST_METHOD(ThreeSymbolBuild) {
			LindenmayerSymbol symbol;
			symbol.SetSymbol('b');
			symbol.SetParameters({ 3.0f, 6.0f });

			LindenmayerSymbolBuilder builder1('v');
			LindenmayerSymbolBuilder builder2('t');
			LindenmayerSymbolBuilder builder3('g');

			ProductionResultGenerator generator({ builder1, builder2, builder3 });

			LindenmayerString result = generator.Generate(symbol);

			Assert::AreEqual((size_t)3, result.Size());
			Assert::AreEqual('v', (*result[0]).GetSymbol());
			Assert::AreEqual('t', (*result[1]).GetSymbol());
			Assert::AreEqual('g', (*result[2]).GetSymbol());
		}

		TEST_METHOD(BuildSymbolWithOneParameter) {
			LindenmayerSymbol symbol;
			symbol.SetSymbol('b');
			symbol.SetParameters({ 3.0f, 6.0f });

			ExpressionBuilder expBldr;
			Expression exp = expBldr.Build("a + b");

			LindenmayerSymbolBuilder builder('v', { exp });

			ProductionResultGenerator generator({ builder });

			LindenmayerString result = generator.Generate(symbol);

			Assert::AreEqual((size_t)1, result.Size());
			Assert::AreEqual('v', (*result[0]).GetSymbol());
			Assert::AreEqual((size_t)1, (*result[0]).GetParameters().size());
			Assert::AreEqual(9.0f, (*result[0]).GetParameters()[0]);
		}

		TEST_METHOD(BuildSymbolWithTwoParameters) {
			LindenmayerSymbol symbol;
			symbol.SetSymbol('b');
			symbol.SetParameters({ 3.0f, 6.0f });

			ExpressionBuilder expBldr;
			Expression exp1 = expBldr.Build("a + b");
			Expression exp2 = expBldr.Build("3 * a");

			LindenmayerSymbolBuilder builder('v', { exp1, exp2 });

			ProductionResultGenerator generator({ builder });

			LindenmayerString result = generator.Generate(symbol);

			Assert::AreEqual((size_t)1, result.Size());
			Assert::AreEqual('v', (*result[0]).GetSymbol());
			Assert::AreEqual((size_t)2, (*result[0]).GetParameters().size());
			Assert::AreEqual(9.0f, (*result[0]).GetParameters()[0]);
			Assert::AreEqual(9.0f, (*result[0]).GetParameters()[1]);
		}

		TEST_METHOD(BuildSymbolWithThreeParameters) {
			LindenmayerSymbol symbol;
			symbol.SetSymbol('b');
			symbol.SetParameters({ 3.0f, 6.0f });

			ExpressionBuilder expBldr;
			Expression exp1 = expBldr.Build("a + b");
			Expression exp2 = expBldr.Build("3 * a");
			Expression exp3 = expBldr.Build("12 / b");

			LindenmayerSymbolBuilder builder('v', { exp1, exp2, exp3 });

			ProductionResultGenerator generator({ builder });

			LindenmayerString result = generator.Generate(symbol);

			Assert::AreEqual((size_t)1, result.Size());
			Assert::AreEqual('v', (*result[0]).GetSymbol());
			Assert::AreEqual((size_t)3, (*result[0]).GetParameters().size());
			Assert::AreEqual(9.0f, (*result[0]).GetParameters()[0]);
			Assert::AreEqual(9.0f, (*result[0]).GetParameters()[1]);
			Assert::AreEqual(2.0f, (*result[0]).GetParameters()[2]);
		}
	};
}