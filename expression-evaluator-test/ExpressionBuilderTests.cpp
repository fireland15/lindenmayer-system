#include "stdafx.h"
#include "CppUnitTest.h"
#include "../expression-evaluator/Expression.h"

#include <map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test {
	TEST_CLASS(ExpressionBuilderTests) {
	public:
		TEST_METHOD(CorrectlyBuildsAndEvaluates) {
			ExpressionBuilder builder;

			auto result = builder.Build("2+3");

			float value = result.Evaluate();;


			Assert::AreEqual(5.0f, value);
		}

		TEST_METHOD(VariableWithNoSetValue) {
			ExpressionBuilder builder;

			Expression expression = builder.Build("a+a");

			expression.SetVariable("a", 3.0f);

			float result = expression.Evaluate();

			Assert::AreEqual(6.0f, result);
		}

		TEST_METHOD(SuperHardTest0) {
			ExpressionBuilder builder;

			Expression expression = builder.Build("(a+b)+(c+d)");

			expression.SetVariable("a", 3.0f);
			expression.SetVariable("b", 3.0f);
			expression.SetVariable("c", 3.0f);
			expression.SetVariable("d", 3.0f);

			float result = expression.Evaluate();

			Assert::AreEqual(12.0f, result);
		}

		TEST_METHOD(SuperHardTest1) {
			ExpressionBuilder builder;

			Expression expression = builder.Build("(3.5 * a) / b - (~d)");

			expression.SetVariable("a", 3.0f);
			expression.SetVariable("b", 3.0f);
			expression.SetVariable("d", 3.0f);

			float result = expression.Evaluate();

			Assert::AreEqual(6.5f, result);
		}

		TEST_METHOD(MultipleTests) {
			std::map<std::string, float> testMap;
			testMap.insert(std::make_pair("0", 0.0f));
			testMap.insert(std::make_pair("1 + 1", 2.0f));
			testMap.insert(std::make_pair("1 * 1", 1.0f));
			testMap.insert(std::make_pair("1 / 1", 1.0f));
			testMap.insert(std::make_pair("1 - 1", 0.0f));
			testMap.insert(std::make_pair("2 - 1", 1.0f));
			testMap.insert(std::make_pair("2 - ~1", 3.0f));
			testMap.insert(std::make_pair("2 * ~1", -2.0f));
			testMap.insert(std::make_pair("2 / ~1", -2.0f));
			testMap.insert(std::make_pair("2 + ~1", 1.0f));
			testMap.insert(std::make_pair("(3 - 4 * (4.5 / 0.5))", -33.0f));
			testMap.insert(std::make_pair("(a - 4 * (b / 0.5))", -33.0f));

			ExpressionBuilder builder;

			for (auto it = testMap.begin(); it != testMap.end(); ++it) {
				Expression expression = builder.Build(it->first);
				
				expression.SetVariable("a", 3.0f);
				expression.SetVariable("b", 4.5f);

				float result = expression.Evaluate();
				Assert::AreEqual(it->second, result);
			}
		}

		TEST_METHOD(ComparisonOperators) {
			std::map<std::string, float> testMap;
			testMap.insert(std::make_pair("1.0 == 1.0", 1.0f));
			testMap.insert(std::make_pair("1.0 == 2.0", 0.0f));
			testMap.insert(std::make_pair("1.0 != 2.0", 1.0f));
			testMap.insert(std::make_pair("1.0 != 1.0", 0.0f));
			testMap.insert(std::make_pair("1.0 > 2.0", 0.0f));
			testMap.insert(std::make_pair("2.0 > 1.0", 1.0f));
			testMap.insert(std::make_pair("1.0 < 2.0", 1.0f));
			testMap.insert(std::make_pair("2.0 < 1.0", 0.0f));
			testMap.insert(std::make_pair("1.0 >= 2.0", 0.0f));
			testMap.insert(std::make_pair("2.0 >= 1.0", 1.0f));
			testMap.insert(std::make_pair("2.0 >= 2.0", 1.0f));
			testMap.insert(std::make_pair("1.0 <= 2.0", 1.0f));
			testMap.insert(std::make_pair("2.0 <= 2.0", 1.0f));
			testMap.insert(std::make_pair("2.0 <= 1.0", 0.0f));

			ExpressionBuilder builder;

			for (auto it = testMap.begin(); it != testMap.end(); ++it) {
				Expression expression = builder.Build(it->first);

				float result = expression.Evaluate();
				Assert::AreEqual(it->second, result);
			}
		}
	};
}