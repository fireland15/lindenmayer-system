#pragma once

#include <vector>

#include "lindenmayer-string.h"
#include "production-rule.h"

class LindenmayerSystem {
private:
	LindenmayerString m_axiom;
	std::vector<ProductionRule> m_rules;

public:
	LindenmayerSystem(LindenmayerString axiom, std::vector<ProductionRule> rules);
	LindenmayerString Run(unsigned int iterations);

private:
	/// <summary>
	/// Selects which rule to apply to the current symbol. Selects the first matching rule.
	/// </summary>
	/// <param name="it"></param>
	/// <returns>The index of the rule matching the current symbol and its context. Returns -1 if no rule matches.</returns>
	int SelectRule(LindenmayerString::Iterator& it);
};;