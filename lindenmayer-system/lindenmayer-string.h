#pragma once

#include "lindenmayer-symbol.h"

#include <vector>

class LindenmayerString {
private:
	std::vector<LindenmayerSymbol> m_symbols;

	LindenmayerString(std::vector<LindenmayerSymbol> symbols)
		: m_symbols(symbols) { }

public:
	LindenmayerString() { }

	LindenmayerString(std::initializer_list<LindenmayerSymbol> symbols)
		: m_symbols(symbols) { }
	
	void Add(LindenmayerSymbol symbol) {
		m_symbols.push_back(symbol);
	}

	LindenmayerSymbol operator[](unsigned int index) const {
		return m_symbols[index];
	}

	unsigned int Size() const {
		return m_symbols.size();
	}

	LindenmayerString SubStr(unsigned int begin, unsigned int end) {
		if (begin >= end)
			return LindenmayerString();

		auto it0 = m_symbols.begin();

		auto it1 = it0 + begin;
		auto it2 = it0 + end;

		if (end >= m_symbols.size())
			it2 = m_symbols.end();
		
		return LindenmayerString(std::vector<LindenmayerSymbol>(it1, it2));
	}

	bool CompareAhead(unsigned int pos, const LindenmayerString& compare) {
		if (pos >= m_symbols.size()) return false;
		if (compare.Size() == 0) return true;
		if (compare.Size() > m_symbols.size() - pos) return false;

		for (unsigned int i = 0; i < compare.Size(); ++i) {
			if (m_symbols[i + pos].GetSymbol() != compare[i].GetSymbol())
				return false;
		}
		return true;
	}

	bool CompareBehind(unsigned int pos, const LindenmayerString& compare) {
		if (pos >= m_symbols.size()) return false;
		if (compare.Size() == 0) return true;

		int s = compare.Size() - 1;
		if (s > pos) return false;

		pos = pos - s;

		for (unsigned int i = 0; i < compare.Size(); ++i) {
			if (m_symbols[i + pos].GetSymbol() != compare[i].GetSymbol())
				return false;
		}

		return true;
	}
};