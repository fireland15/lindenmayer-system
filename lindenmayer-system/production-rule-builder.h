#pragma once

#include "production-rule.h"
#include "production-parser.h"
#include "context-inspector-builder.h"

class ProductionRuleBuilder {
private:
	ContextInspectorBuilder m_contextInspectorBuilder;

public:
	ProductionRule Build(std::string& productionString) {
		std::string preContext;
		std::string postContext;
		char symbol;
		std::string result;

		ParseProductionString(productionString, preContext, postContext, result, symbol);
		
		return std::move(Build(preContext, postContext, symbol, result));
	}

	ProductionRule Build(std::string& preContext, std::string& postContext, char symbol, std::string& result) {
		ContextInspector contextInspector = m_contextInspectorBuilder.Build(preContext, postContext);

		std::vector<LindenmayerSymbolBuilder> resultBuilders;
		std::vector<std::pair<char, std::vector<Expression>>> resultSymbolMap = StrToLstrConverter().ResultConvert(result);

		for (unsigned int i = 0; i < resultSymbolMap.size(); i++) {
			char symbol = resultSymbolMap[i].first;
			std::vector<Expression> expressions = resultSymbolMap[i].second;
			LindenmayerSymbolBuilder builder(symbol, expressions);
			resultBuilders.push_back(builder);
		}

		ProductionResultGenerator resultGenerator(resultBuilders);

		return ProductionRule(symbol, std::move(contextInspector), resultGenerator);
	}

private:
	void ParseProductionString(const std::string& productionString, std::string& preContext, std::string& postContext, std::string& result, char& symbol) {
		ProductionStringParser parser(productionString);
		preContext = parser.GetPreContext();
		postContext = parser.GetPostContext();
		symbol = parser.GetSymbol();
		result = parser.GetResult();
	}
};