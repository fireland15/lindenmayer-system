#include "stdafx.h"
#include "CppUnitTest.h"
#include "../expression-evaluator/InfixToPostfixConverter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test {
	TEST_CLASS(InfixToPostfixConverterTests) {
	public:
		TEST_METHOD(EmptyTokenList) {
			TokenList tokens;

			std::map<OperatorType, std::pair<Associativity, Precedence>> opMap;
			opMap[OperatorType::add] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::sub] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::neg] = std::make_pair(Associativity::right, Precedence::mid);
			opMap[OperatorType::mul] = std::make_pair(Associativity::left, Precedence::high);
			opMap[OperatorType::div] = std::make_pair(Associativity::left, Precedence::high);

			InfixToPostfixConverter converter(opMap);

			TokenList result = converter(tokens);

			Assert::IsTrue(result.empty());
		}

		TEST_METHOD(SingleTokenInList1) {
			TokenList tokens;
			tokens.push_back(Token(3.14f));

			std::map<OperatorType, std::pair<Associativity, Precedence>> opMap;
			opMap[OperatorType::add] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::sub] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::neg] = std::make_pair(Associativity::right, Precedence::mid);
			opMap[OperatorType::mul] = std::make_pair(Associativity::left, Precedence::high);
			opMap[OperatorType::div] = std::make_pair(Associativity::left, Precedence::high);

			InfixToPostfixConverter converter(opMap);

			TokenList result = converter(tokens);

			Assert::AreEqual(1, (int)result.size());
			Assert::AreEqual(3.14f, result.front().Value());
		}

		TEST_METHOD(SingleTokenInList2) {
			TokenList tokens;
			tokens.push_back(Token("test_var"));

			std::map<OperatorType, std::pair<Associativity, Precedence>> opMap;
			opMap[OperatorType::add] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::sub] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::neg] = std::make_pair(Associativity::right, Precedence::mid);
			opMap[OperatorType::mul] = std::make_pair(Associativity::left, Precedence::high);
			opMap[OperatorType::div] = std::make_pair(Associativity::left, Precedence::high);

			InfixToPostfixConverter converter(opMap);

			TokenList result = converter(tokens);

			Assert::AreEqual(1, (int)result.size());
			Assert::AreEqual("test_var", result.front().Symbol().c_str());
		}

		TEST_METHOD(SimpleAddition) {
			TokenList tokens;
			tokens.push_back(Token("A"));
			tokens.push_back(Token(OperatorType::add));
			tokens.push_back(Token("B"));

			std::map<OperatorType, std::pair<Associativity, Precedence>> opMap;
			opMap[OperatorType::add] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::sub] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::neg] = std::make_pair(Associativity::right, Precedence::mid);
			opMap[OperatorType::mul] = std::make_pair(Associativity::left, Precedence::high);
			opMap[OperatorType::div] = std::make_pair(Associativity::left, Precedence::high);

			InfixToPostfixConverter converter(opMap);

			TokenList result = converter(tokens);

			Assert::AreEqual(3, (int)result.size());

			auto it = result.begin();
			Assert::AreEqual("A", (*it++).Symbol().c_str());
			Assert::AreEqual("B", (*it++).Symbol().c_str());
			Assert::AreEqual((int)OperatorType::add, (int)(*it).Operator());
		}

		TEST_METHOD(MultipleOperators) {
			TokenList tokens;
			tokens.push_back(Token("A"));
			tokens.push_back(Token(OperatorType::add));
			tokens.push_back(Token("B"));
			tokens.push_back(Token(OperatorType::sub));
			tokens.push_back(Token("C"));
			
			std::map<OperatorType, std::pair<Associativity, Precedence>> opMap;
			opMap[OperatorType::add] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::sub] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::neg] = std::make_pair(Associativity::right, Precedence::mid);
			opMap[OperatorType::mul] = std::make_pair(Associativity::left, Precedence::high);
			opMap[OperatorType::div] = std::make_pair(Associativity::left, Precedence::high);

			InfixToPostfixConverter converter(opMap);

			TokenList result = converter(tokens);

			Assert::AreEqual(5, (int)result.size());

			auto it = result.begin();
			Assert::AreEqual("A", (*it++).Symbol().c_str());
			Assert::AreEqual("B", (*it++).Symbol().c_str());
			Assert::AreEqual((int)OperatorType::add, (int)(*it++).Operator());
			Assert::AreEqual("C", (*it++).Symbol().c_str());
			Assert::AreEqual((int)OperatorType::sub, (int)(*it).Operator());
		}

		TEST_METHOD(MultipleOperatorsDifferentAssociativity) {
			TokenList tokens;
			tokens.push_back(Token("A"));
			tokens.push_back(Token(OperatorType::add));
			tokens.push_back(Token("B"));
			tokens.push_back(Token(OperatorType::mul));
			tokens.push_back(Token("C"));

			std::map<OperatorType, std::pair<Associativity, Precedence>> opMap;
			opMap[OperatorType::add] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::sub] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::neg] = std::make_pair(Associativity::right, Precedence::mid);
			opMap[OperatorType::mul] = std::make_pair(Associativity::left, Precedence::high);
			opMap[OperatorType::div] = std::make_pair(Associativity::left, Precedence::high);

			InfixToPostfixConverter converter(opMap);

			TokenList result = converter(tokens);

			Assert::AreEqual(5, (int)result.size());

			auto it = result.begin();
			Assert::AreEqual("A", (*it++).Symbol().c_str());
			Assert::AreEqual("B", (*it++).Symbol().c_str());
			Assert::AreEqual("C", (*it++).Symbol().c_str());
			Assert::AreEqual((int)OperatorType::mul, (int)(*it++).Operator());
			Assert::AreEqual((int)OperatorType::add, (int)(*it).Operator());
		}

		TEST_METHOD(SimpleParenthesis) {
			TokenList tokens;
			tokens.push_back(Token(TokenType::LParen));
			tokens.push_back(Token("A"));
			tokens.push_back(Token(OperatorType::add));
			tokens.push_back(Token("B"));
			tokens.push_back(Token(TokenType::RParen));
			
			std::map<OperatorType, std::pair<Associativity, Precedence>> opMap;
			opMap[OperatorType::add] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::sub] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::neg] = std::make_pair(Associativity::right, Precedence::mid);
			opMap[OperatorType::mul] = std::make_pair(Associativity::left, Precedence::high);
			opMap[OperatorType::div] = std::make_pair(Associativity::left, Precedence::high);

			InfixToPostfixConverter converter(opMap);

			TokenList result = converter(tokens);

			Assert::AreEqual(3, (int)result.size());

			auto it = result.begin();
			Assert::AreEqual("A", (*it++).Symbol().c_str());
			Assert::AreEqual("B", (*it++).Symbol().c_str());
			Assert::AreEqual((int)OperatorType::add, (int)(*it).Operator());
		}

		TEST_METHOD(LessSimpleParenthesis) {
			TokenList tokens;
			tokens.push_back(Token(TokenType::LParen));
			tokens.push_back(Token("A"));
			tokens.push_back(Token(OperatorType::add));
			tokens.push_back(Token("B"));
			tokens.push_back(Token(TokenType::RParen));
			tokens.push_back(Token(OperatorType::mul));
			tokens.push_back(Token(3.0f));
			
			std::map<OperatorType, std::pair<Associativity, Precedence>> opMap;
			opMap[OperatorType::add] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::sub] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::neg] = std::make_pair(Associativity::right, Precedence::mid);
			opMap[OperatorType::mul] = std::make_pair(Associativity::left, Precedence::high);
			opMap[OperatorType::div] = std::make_pair(Associativity::left, Precedence::high);

			InfixToPostfixConverter converter(opMap);

			TokenList result = converter(tokens);

			Assert::AreEqual(5, (int)result.size());

			auto it = result.begin();
			Assert::AreEqual("A", (*it++).Symbol().c_str());
			Assert::AreEqual("B", (*it++).Symbol().c_str());
			Assert::AreEqual((int)OperatorType::add, (int)(*it++).Operator());
			Assert::AreEqual(3.0f, (*it++).Value());
			Assert::AreEqual((int)OperatorType::mul, (int)(*it).Operator());
		}

		TEST_METHOD(TwoSetsOfParenthesis) {
			TokenList tokens;
			tokens.push_back(Token(TokenType::LParen));
			tokens.push_back(Token("A"));
			tokens.push_back(Token(OperatorType::add));
			tokens.push_back(Token("B"));
			tokens.push_back(Token(TokenType::RParen));
			tokens.push_back(Token(OperatorType::mul));
			tokens.push_back(Token(TokenType::LParen));
			tokens.push_back(Token("A"));
			tokens.push_back(Token(OperatorType::add));
			tokens.push_back(Token("B"));
			tokens.push_back(Token(TokenType::RParen));
			
			std::map<OperatorType, std::pair<Associativity, Precedence>> opMap;
			opMap[OperatorType::add] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::sub] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::neg] = std::make_pair(Associativity::right, Precedence::mid);
			opMap[OperatorType::mul] = std::make_pair(Associativity::left, Precedence::high);
			opMap[OperatorType::div] = std::make_pair(Associativity::left, Precedence::high);

			InfixToPostfixConverter converter(opMap);

			TokenList result = converter(tokens);

			Assert::AreEqual(7, (int)result.size());

			auto it = result.begin();
			Assert::AreEqual("A", (*it++).Symbol().c_str());
			Assert::AreEqual("B", (*it++).Symbol().c_str());
			Assert::AreEqual((int)OperatorType::add, (int)(*it++).Operator());
			Assert::AreEqual("A", (*it++).Symbol().c_str());
			Assert::AreEqual("B", (*it++).Symbol().c_str());
			Assert::AreEqual((int)OperatorType::add, (int)(*it++).Operator());
			Assert::AreEqual((int)OperatorType::mul, (int)(*it).Operator());
		}

		TEST_METHOD(NestedParenthesis) {
			TokenList tokens;
			tokens.push_back(Token(TokenType::LParen));
			tokens.push_back(Token("C"));
			tokens.push_back(Token(OperatorType::add));
			tokens.push_back(Token(TokenType::LParen));
			tokens.push_back(Token("A"));
			tokens.push_back(Token(OperatorType::add));
			tokens.push_back(Token("B"));
			tokens.push_back(Token(TokenType::RParen));
			tokens.push_back(Token(TokenType::RParen));
			
			std::map<OperatorType, std::pair<Associativity, Precedence>> opMap;
			opMap[OperatorType::add] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::sub] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::neg] = std::make_pair(Associativity::right, Precedence::mid);
			opMap[OperatorType::mul] = std::make_pair(Associativity::left, Precedence::high);
			opMap[OperatorType::div] = std::make_pair(Associativity::left, Precedence::high);

			InfixToPostfixConverter converter(opMap);

			TokenList result = converter(tokens);

			Assert::AreEqual(5, (int)result.size());

			auto it = result.begin();
			Assert::AreEqual("C", (*it++).Symbol().c_str());
			Assert::AreEqual("A", (*it++).Symbol().c_str());
			Assert::AreEqual("B", (*it++).Symbol().c_str());
			Assert::AreEqual((int)OperatorType::add, (int)(*it++).Operator());
			Assert::AreEqual((int)OperatorType::add, (int)(*it).Operator());
		}

		TEST_METHOD(DifferentAssociations) {
			TokenList tokens;
			tokens.push_back(Token(OperatorType::neg));
			tokens.push_back(Token("A"));
			tokens.push_back(Token(OperatorType::add));
			tokens.push_back(Token("B"));

			std::map<OperatorType, std::pair<Associativity, Precedence>> opMap;
			opMap[OperatorType::add] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::sub] = std::make_pair(Associativity::left, Precedence::low);
			opMap[OperatorType::neg] = std::make_pair(Associativity::right, Precedence::mid);
			opMap[OperatorType::mul] = std::make_pair(Associativity::left, Precedence::high);
			opMap[OperatorType::div] = std::make_pair(Associativity::left, Precedence::high);

			InfixToPostfixConverter converter(opMap);

			TokenList result = converter(tokens);

			Assert::AreEqual(4, (int)result.size());

			auto it = result.begin();
			Assert::AreEqual("A", (*it++).Symbol().c_str());
			Assert::AreEqual((int)OperatorType::neg, (int)(*it++).Operator());
			Assert::AreEqual("B", (*it++).Symbol().c_str());
			Assert::AreEqual((int)OperatorType::add, (int)(*it).Operator());
		}
	};
}