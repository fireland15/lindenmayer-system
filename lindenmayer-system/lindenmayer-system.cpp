#include "lindenmayer-system.h"

LindenmayerSystem::LindenmayerSystem(LindenmayerString axiom, std::vector<ProductionRule> rules)
	: m_axiom(axiom), m_rules(std::move(rules)) { }

LindenmayerString LindenmayerSystem::Run(unsigned int iterations) {
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

int LindenmayerSystem::SelectRule(LindenmayerString::Iterator& it) {
	for (unsigned int i = 0; i < m_rules.size(); i++) {
		if (m_rules[i].CanReplace(it))
			return i;
	}
	return -1;
}

void LindenmayerSystem::AddRule(ProductionRule rule) {
	m_rules.push_back(std::move(rule));
}