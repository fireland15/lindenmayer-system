#pragma once

#include <string>

struct ProductionRuleCreateDesc {
	std::string preContext;
	std::string postContext;
	char symbol;
	std::string result;
};