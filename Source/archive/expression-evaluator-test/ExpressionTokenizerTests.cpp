#include "stdafx.h"
#include "CppUnitTest.h"
#include "../expression-evaluator/expression-tokenizer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test {
	TEST_CLASS(ExpressionTokenizerTests) {
	public:
		TEST_METHOD(CreatesValueToken) {
			std::string expression("3.14159");

			OperatorMap opMap;
			opMap["~"] = OperatorType::neg;
			opMap["+"] = OperatorType::add;
			opMap["-"] = OperatorType::sub;
			opMap["*"] = OperatorType::mul;
			opMap["/"] = OperatorType::div;
			
			ExpressionTokenizer tokenizer(opMap);
			TokenList result = tokenizer(expression);

			Assert::AreEqual(1, (int)result.size());
			Assert::AreEqual((int)(TokenType::Value), (int)(result.front().Type()));
			Assert::AreEqual(3.14159f, result.front().Value());
		}

		TEST_METHOD(CreatesOperatorToken) {
			std::string expression("+");

			OperatorMap opMap;
			opMap["~"] = OperatorType::neg;
			opMap["+"] = OperatorType::add;
			opMap["-"] = OperatorType::sub;
			opMap["*"] = OperatorType::mul;
			opMap["/"] = OperatorType::div;

			ExpressionTokenizer tokenizer(opMap);
			TokenList result = tokenizer(expression);

			Assert::AreEqual(1, (int)result.size());
			Assert::AreEqual((int)(TokenType::Operator), (int)(result.front().Type()));
			Assert::AreEqual((int)OperatorType::add, (int)(result.front().Operator()));
		}

		TEST_METHOD(CreatesVariableToken) {
			std::string expression("token");

			OperatorMap opMap;
			opMap["~"] = OperatorType::neg;
			opMap["+"] = OperatorType::add;
			opMap["-"] = OperatorType::sub;
			opMap["*"] = OperatorType::mul;
			opMap["/"] = OperatorType::div;

			ExpressionTokenizer tokenizer(opMap);
			TokenList result = tokenizer(expression);

			Assert::AreEqual(1, (int)result.size());
			Assert::AreEqual((int)(TokenType::Identifier), (int)(result.front().Type()));
			Assert::AreEqual(std::string("token"), result.front().Symbol());
		}

		TEST_METHOD(CreatesLeftParenthesisToken) {
			std::string expression("(");

			OperatorMap opMap;
			opMap["~"] = OperatorType::neg;
			opMap["+"] = OperatorType::add;
			opMap["-"] = OperatorType::sub;
			opMap["*"] = OperatorType::mul;
			opMap["/"] = OperatorType::div;

			ExpressionTokenizer tokenizer(opMap);
			TokenList result = tokenizer(expression);

			Assert::AreEqual(1, (int)result.size());
			Assert::AreEqual((int)(TokenType::LParen), (int)(result.front().Type()));
		}

		TEST_METHOD(CreatesRightParenthesisToken) {
			std::string expression(")");

			OperatorMap opMap;
			opMap["~"] = OperatorType::neg;
			opMap["+"] = OperatorType::add;
			opMap["-"] = OperatorType::sub;
			opMap["*"] = OperatorType::mul;
			opMap["/"] = OperatorType::div;

			ExpressionTokenizer tokenizer(opMap);
			TokenList result = tokenizer(expression);

			Assert::AreEqual(1, (int)result.size());
			Assert::AreEqual((int)(TokenType::RParen), (int)(result.front().Type()));
		}

		TEST_METHOD(MultipleTokens0) {
			std::string expression("()");

			OperatorMap opMap;
			opMap["~"] = OperatorType::neg;
			opMap["+"] = OperatorType::add;
			opMap["-"] = OperatorType::sub;
			opMap["*"] = OperatorType::mul;
			opMap["/"] = OperatorType::div;

			ExpressionTokenizer tokenizer(opMap);
			TokenList result = tokenizer(expression);

			Assert::AreEqual(2, (int)result.size());
			auto it = result.begin();
			Assert::AreEqual((int)(TokenType::LParen), (int)(*it++).Type());

			Assert::AreEqual((int)(TokenType::RParen), (int)(*it++).Type());
		}

		TEST_METHOD(MultipleTokens1) {
			std::string expression("(3.14159)");

			OperatorMap opMap;
			opMap["~"] = OperatorType::neg;
			opMap["+"] = OperatorType::add;
			opMap["-"] = OperatorType::sub;
			opMap["*"] = OperatorType::mul;
			opMap["/"] = OperatorType::div;

			ExpressionTokenizer tokenizer(opMap);
			TokenList result = tokenizer(expression);

			Assert::AreEqual(3, (int)result.size());

			auto it = result.begin();
			Assert::AreEqual((int)(TokenType::LParen), (int)(*it++).Type());

			Assert::AreEqual((int)(TokenType::Value), (int)(*it).Type());
			Assert::AreEqual(3.14159f, (*it++).Value());

			Assert::AreEqual((int)(TokenType::RParen), (int)(*it++).Type());
		}

		TEST_METHOD(MultipleTokens2) {
			std::string expression("(3.14159+c) / 3");

			OperatorMap opMap;
			opMap["~"] = OperatorType::neg;
			opMap["+"] = OperatorType::add;
			opMap["-"] = OperatorType::sub;
			opMap["*"] = OperatorType::mul;
			opMap["/"] = OperatorType::div;

			ExpressionTokenizer tokenizer(opMap);
			TokenList result = tokenizer(expression);

			Assert::AreEqual(7, (int)result.size());

			auto it = result.begin();
			Assert::AreEqual((int)TokenType::LParen, (int)(*it++).Type());

			Assert::AreEqual((int)TokenType::Value, (int)(*it).Type());
			Assert::AreEqual(3.14159f, (*it++).Value());

			Assert::AreEqual((int)TokenType::Operator, (int)(*it).Type());
			Assert::AreEqual((int)OperatorType::add, (int)(*it++).Operator());

			Assert::AreEqual((int)TokenType::Identifier, (int)(*it).Type());
			Assert::AreEqual(std::string("c"), (*it++).Symbol());

			Assert::AreEqual((int)(TokenType::RParen), (int)(*it++).Type());

			Assert::AreEqual((int)TokenType::Operator, (int)(*it).Type());
			Assert::AreEqual((int)OperatorType::div, (int)(*it++).Operator());

			Assert::AreEqual((int)TokenType::Value, (int)(*it).Type());
			Assert::AreEqual(3.00f, (*it++).Value());
		}
	};
}