#pragma once

#include <string>

#include "context-inspector.h"
#include "production-rule.h"
#include "production-rule-create-desc.h"
#include "production-parser.h"
#include "../expression-evaluator/expression-builder.h"

ContextInspector BuildContextInspector(std::string& preContext, std::string& postContext);

LindenmayerString* ContextConvert(std::string& str);

/// <summary>
/// Parses the result string into pairs of symbols and the expressions for that functions parameters.
/// Must be of form x(y,z,...)-w(...)-...
/// </summary>
/// <param name="str">
/// The result string.
/// </param>
std::vector<std::pair<char, std::vector<Expression>>> ResultConvert(std::string& str);

ProductionRule CreateProductionRule(std::string& productionString);

ProductionRule CreateProductionRule(ProductionRuleCreateDesc& desc);

ProductionRuleCreateDesc ParseProductionString(std::string& str);
