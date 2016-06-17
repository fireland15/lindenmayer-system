#pragma once

#include <string>

#include "lindenmayer-string.h"
#include "../expression-evaluator/expression-builder.h"
#include "../expression-evaluator/expression.h"

class StrToLstrConverter {
public:
	static LindenmayerString* ContextConvert(std::string& str) {
		LindenmayerString* lstr = new LindenmayerString;
		std::string::iterator si = str.begin();

		while (si != str.end()) {
			LindenmayerSymbol symbol;

			if (std::isalpha(*si)) {
				symbol.SetSymbol(*si);
				si++;
				if (si != str.end() && *si == '(') { // dereferencing end iterator
					si++;
					while (si != str.end() && *si != ')') {
						si++;
					}
					if (si != str.end()) si++;
				}
				lstr->Add(symbol);
			}
		}
		return (lstr->Size() > 0) ? lstr : nullptr;
	}

	// of form x(xx,xx,x,...)-x(...)-...
	static std::vector<std::pair<char, std::vector<Expression>>> ResultConvert(std::string& str) {
		std::vector<std::pair<char, std::vector<Expression>>> map;

		std::stringstream ss(str);
		std::vector<std::string> symbolStr;
		ExpressionBuilder builder;

		std::string s;
		while (std::getline(ss, s, '-')) {
			symbolStr.push_back(s);
		}
		
		for (std::string s : symbolStr) {
			if (std::isalpha(s[0]) && s[1] == '(' && s[s.size() - 1] == ')') {
				char symbol = s[0];
				std::vector<Expression> list;

				if (s.size() == 3) {
					map.push_back(std::make_pair(symbol, list));
					continue;
				}

				std::stringstream paramExpressions(s.substr(2, s.size() - 3));
				
				std::string exp;
				while (std::getline(paramExpressions, exp, ',')) {
					if (exp == "") {
						break;
					}
					Expression expression = builder.Build(exp);
					list.push_back(expression);
				}
				map.push_back(std::make_pair(symbol, list));
			}
			else {
				throw std::exception("Results string not proper");
			}
		}

		return map;
	}
};