#include "factories.h"

ContextInspector BuildContextInspector(std::string & preContext, std::string & postContext)
{
	LindenmayerString* pPreLstr = ContextConvert(preContext);
	LindenmayerString* pPostLstr = ContextConvert(postContext);

	ContextInspector inspector(pPreLstr, pPostLstr);

	return inspector;
}

LindenmayerString* ContextConvert(std::string& str) {
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

std::vector<std::pair<char, std::vector<Expression>>> ResultConvert(std::string& str) {
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

ProductionRule CreateProductionRule(std::string & productionString)
{
	return std::move(CreateProductionRule(ParseProductionString(productionString)));
}

ProductionRule CreateProductionRule(ProductionRuleCreateDesc & desc)
{
	ContextInspector contextInspector = BuildContextInspector(desc.preContext, desc.postContext);

	std::vector<LindenmayerSymbolBuilder> resultBuilders;
	std::vector<std::pair<char, std::vector<Expression>>> resultSymbolMap = ResultConvert(desc.result);

	for (unsigned int i = 0; i < resultSymbolMap.size(); ++i) {
		char symbol = resultSymbolMap[i].first;
		std::vector<Expression> expressions = resultSymbolMap[i].second;
		LindenmayerSymbolBuilder builder(symbol, expressions);
		resultBuilders.push_back(builder);
	}

	ProductionResultGenerator resultGenerator(resultBuilders);

	return ProductionRule(desc.symbol, std::move(contextInspector), resultGenerator);
}

ProductionRuleCreateDesc ParseProductionString(std::string & str)
{
	ProductionStringParser parser(str);

	return {
		parser.GetPreContext(),
		parser.GetPostContext(),
		parser.GetSymbol(),
		parser.GetResult()
	};
}
