#pragma once

#include <list>
#include <stack>
#include <map>

#include "Token.h"
#include "Exceptions.h"

typedef std::list<Token> TokenList;

class InfixToPostfixConverter {
private:
	std::map<OperatorType, std::pair<Associativity, Precedence>> m_operatorMap;
public:
	InfixToPostfixConverter(std::map<OperatorType, std::pair<Associativity, Precedence>>& operatorMap)
		: m_operatorMap(operatorMap) { }

	TokenList operator()(const TokenList& in) const {
		if (in.empty())
			return TokenList();

		TokenList out;
		std::stack<Token> opstk;

		for (auto it = in.begin(); it != in.end(); ++it) {
			Token token = *it;

			switch (token.Type()) {
			case TokenType::Value:
			case TokenType::Identifier:
				out.push_back(token);
				break;

			case TokenType::Operator:
				while (!opstk.empty() && TestPrecedence(token, opstk.top())) {
					out.push_back(opstk.top());
					opstk.pop();
				}
				opstk.push(token);
				break;

			case TokenType::LParen:
				opstk.push(token);
				break;

			case TokenType::RParen:
				if (opstk.empty())
					throw ParseException("Unmatched Parenthesis");
				while (opstk.top().Type() != TokenType::LParen) {
					out.push_back(opstk.top());
					opstk.pop();

					if (opstk.empty())
						throw ParseException("Unmatched Parenthesis");
				}
				opstk.pop();
				break;

			default:
				break;
			}
		}

		while (!opstk.empty()) {
			Token token = opstk.top();
			if (token.Type() == TokenType::LParen || token.Type() == TokenType::RParen)
				throw ParseException("Unmatched Parenthesis");
			out.push_back(token);
			opstk.pop();
		}

		return out;
	}

private:
	bool TestPrecedence(const Token& t1, const Token& t2) const {
		if (t2.Type() == TokenType::LParen)
			return false;

		auto t1Data = m_operatorMap.find(t1.OperatorType())->second;
		auto t2Data = m_operatorMap.find(t2.OperatorType())->second;



		if (t1Data.first == Associativity::left && t1Data.second <= t2Data.second)
			return true;
		if (t1Data.first == Associativity::right && t1Data.second < t2Data.second)
			return true;
		return false;
	}
};