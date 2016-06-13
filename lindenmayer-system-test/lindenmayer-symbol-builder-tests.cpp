#include "stdafx.h"
#include "CppUnitTest.h"

#include "../expression-evaluator/expression-builder.h"
#include "../expression-evaluator/expression.h"
#include "../lindenmayer-system/lindenmayer-symbol.h"
#include "../lindenmayer-system/lindenmayer-symbol-builder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lindenmayersystemtest {
	TEST_CLASS(LindenmayerSymbolBuilderTests) {
	public:

		TEST_METHOD(NoParameters) {
			LindenmayerSymbolBuilder builder('a');
			LindenmayerSymbol symbol = builder.BuildSymbol();

			Assert::AreEqual('a', symbol.symbol);
			Assert::AreEqual((size_t)0, symbol.parameters.size());
		}

		TEST_METHOD(SingleParameter) {
			ExpressionBuilder exBuilder;
			Expression exp = exBuilder.Build("1+3");

			LindenmayerSymbolBuilder builder('a', { exp });
			LindenmayerSymbol symbol = builder.BuildSymbol();

			Assert::AreEqual('a', symbol.symbol);
			Assert::AreEqual((size_t)1, symbol.parameters.size());
			Assert::AreEqual(4.0f, symbol.parameters[0]);
		}

		TEST_METHOD(TwoParameters) {
			ExpressionBuilder exBuilder;
			Expression exp1 = exBuilder.Build("1+3");
			Expression exp2 = exBuilder.Build("e + 45 / 32");
			exp2.SetVariable("e", 4.0f);

			LindenmayerSymbolBuilder builder('a', { exp1, exp2 });
			LindenmayerSymbol symbol = builder.BuildSymbol();

			Assert::AreEqual('a', symbol.symbol);
			Assert::AreEqual((size_t)2, symbol.parameters.size());
			Assert::AreEqual(4.0f, symbol.parameters[0]);
			Assert::AreEqual(5.40625f, symbol.parameters[1]);
		}

		TEST_METHOD(ThreeParameters) {
			ExpressionBuilder exBuilder;
			Expression exp1 = exBuilder.Build("1+3");
			Expression exp2 = exBuilder.Build("e + 45 / 32");
			exp2.SetVariable("e", 4.0f);
			Expression exp3 = exBuilder.Build("3 + 3 * (33 - 3)");

			LindenmayerSymbolBuilder builder('a', { exp1, exp2, exp3 });
			LindenmayerSymbol symbol = builder.BuildSymbol();

			Assert::AreEqual('a', symbol.symbol);
			Assert::AreEqual((size_t)3, symbol.parameters.size());
			Assert::AreEqual(4.0f, symbol.parameters[0]);
			Assert::AreEqual(5.40625f, symbol.parameters[1]);
			Assert::AreEqual(93.0f, symbol.parameters[2]);
		}

		TEST_METHOD(TwoSymbolsDifferentValues) {
			ExpressionBuilder exBuilder;
			Expression exp = exBuilder.Build("x + 3");
			LindenmayerSymbolBuilder builder('a', { exp });

			builder.PassParameter("x", 2.0f);
			LindenmayerSymbol symbol1 = builder.BuildSymbol();

			builder.PassParameter("x", 7.0f);
			LindenmayerSymbol symbol2 = builder.BuildSymbol();

			Assert::AreEqual(5.0f, symbol1.parameters[0]);
			Assert::AreEqual(10.0f, symbol2.parameters[0]);
		}
	};
}