#include "stdafx.h"
#include "CppUnitTest.h"
#include "../expression-evaluator/ExpressionNodes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test {		
	TEST_CLASS(ExpressionNodeBuilderTests) {
	public:
		TEST_METHOD(CreatesNegate) {
			Token token(OperatorType::neg);

			ExpressionNodeBuilder builder;

			auto result = builder.NewExpressionNode(token);

			Assert::IsNotNull(result);
			Assert::IsTrue(dynamic_cast<UnaryOperatorNode*>(result) != nullptr);
		}

		TEST_METHOD(CreatesAddition) {
			Token token(OperatorType::add);

			ExpressionNodeBuilder builder;

			auto result = builder.NewExpressionNode(token);

			Assert::IsNotNull(result);
			Assert::IsTrue(dynamic_cast<BinaryOperatorNode*>(result) != nullptr);
		}

		TEST_METHOD(CreatesSubtraction) {
			Token token(OperatorType::sub);

			ExpressionNodeBuilder builder;

			auto result = builder.NewExpressionNode(token);

			Assert::IsNotNull(result);
			Assert::IsTrue(dynamic_cast<BinaryOperatorNode*>(result) != nullptr);
		}

		TEST_METHOD(CreatesMultiplication) {
			Token token(OperatorType::mul);

			ExpressionNodeBuilder builder;

			auto result = builder.NewExpressionNode(token);

			Assert::IsNotNull(result);
			Assert::IsTrue(dynamic_cast<BinaryOperatorNode*>(result) != nullptr);
		}

		TEST_METHOD(CreatesDivision) {
			Token token(OperatorType::div);

			ExpressionNodeBuilder builder;

			auto result = builder.NewExpressionNode(token);

			Assert::IsNotNull(result);
			Assert::IsTrue(dynamic_cast<BinaryOperatorNode*>(result) != nullptr);
		}

		TEST_METHOD(CreatesValueNode) {
			Token token(3.14159f);

			ExpressionNodeBuilder builder;

			auto result = builder.NewExpressionNode(token);

			Assert::IsNotNull(result);
			Assert::IsTrue(dynamic_cast<ValueNode*>(result) != nullptr);
		}

		TEST_METHOD(CreatesVariableNode) {
			Token token("test");

			ExpressionNodeBuilder builder;

			auto result = builder.NewExpressionNode(token);

			Assert::IsNotNull(result);
			Assert::IsTrue(dynamic_cast<VariableNode*>(result) != nullptr);
		}

		TEST_METHOD(VariableMapGetsUpdated) {
			Token token("test");

			ExpressionNodeBuilder builder;

			builder.NewExpressionNode(token);

			auto result = builder.GetVariableMap();

			Assert::IsTrue(result.find("test") != result.end());
			Assert::IsNotNull(result.find("test")->second.front());
		}
	};

	TEST_CLASS(NodesEvalute) {
	public:
		TEST_METHOD(Negate) {
			UnaryOperatorNode negate([](float x) {return -1 * x;});
			ValueNode node(3.14f);
			negate.SetChild(&node);
			
			auto result = negate();

			Assert::AreEqual(-3.14f, result);
		}

		TEST_METHOD(Addition) {
			BinaryOperatorNode addition([](float x, float y) { return x + y; });
			ValueNode node1(3.14f);
			ValueNode node2(1.00f);
			addition.SetChild(&node1, 0);
			addition.SetChild(&node2, 1);

			auto result = addition();

			Assert::AreEqual(3.14f + 1.00f, result);
		}
		
		TEST_METHOD(Multiplication) {
			BinaryOperatorNode mulitply([](float x, float y) { return x * y; });
			ValueNode node1(3.14f);
			ValueNode node2(1.00f);
			mulitply.SetChild(&node1, 0);
			mulitply.SetChild(&node2, 1);

			auto result = mulitply();

			Assert::AreEqual(3.14f * 1.00f, result);
		}

		TEST_METHOD(Subtraction) {
			BinaryOperatorNode subtract([](float x, float y) { return x - y; });
			ValueNode node1(3.14f);
			ValueNode node2(1.00f);
			subtract.SetChild(&node1, 0);
			subtract.SetChild(&node2, 1);

			auto result = subtract();

			Assert::AreEqual(3.14f - 1.00f, result);
		}

		TEST_METHOD(Division) {
			BinaryOperatorNode division([](float x, float y) { return x / y; });
			ValueNode node1(3.14f);
			ValueNode node2(1.00f);
			division.SetChild(&node1, 0);
			division.SetChild(&node2, 1);

			auto result = division();

			Assert::AreEqual(3.14f / 1.00f, result);
		}
	};
}