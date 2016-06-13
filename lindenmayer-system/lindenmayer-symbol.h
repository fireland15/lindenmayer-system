#pragma once

#include <vector>

#include "../expression-evaluator/expression.h"

struct LindenmayerSymbol {
	char symbol;
	std::vector<float> parameters;

	std::string ToString() {
		throw std::exception();
	}
};