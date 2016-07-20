#pragma once

#include <vector>

#include "lindenmayer-string.h"
#include "production-rule.h"

class LindenmayerSystem {
private:
	LindenmayerString m_axiom;
	std::vector<ProductionRule> m_rules;

public:
	LindenmayerSystem(LindenmayerString axiom, std::vector<ProductionRule> rules)
		: m_axiom(axiom), m_rules(std::move(rules)) { }

	LindenmayerString Run(unsigned int iterations) { 
		LindenmayerString current = m_axiom;
		LindenmayerString next;

		while (iterations-- > 0) {
			for (unsigned int i = 0; i < current.Size(); i++) {
				int ruleIndex = SelectRule(current[i]);
				if (ruleIndex == -1) {
					next.Add(current[i]);
				}
				else {
					LindenmayerString stub = m_rules[ruleIndex].Produce(*current[i]);
					next.Add(stub);
				}
			}

			swap(current, next);
			next.Clear();
		}

		return current;
	}

	// Todo: Set global variables and have them propagate through all systems.

private:
	/// <summary>
	/// Selects which rule to apply to the current symbol. Selects the first matching rule.
	/// </summary>
	/// <param name="it"></param>
	/// <returns>The index of the rule matching the current symbol and its context. Returns -1 if no rule matches.</returns>
	int SelectRule(LindenmayerString::Iterator& it) {
		for (unsigned int i = 0; i < m_rules.size(); i++) {
			if (m_rules[i].CanReplace(it))
				return i;
		}
		return -1;
	}
};;