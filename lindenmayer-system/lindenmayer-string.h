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

	class Iterator {
	private:
		LindenmayerString& m_parent;
		int m_pos;

	public:
		Iterator(LindenmayerString& parent) 
			: m_parent(parent), m_pos(0) { } // Defaults to begining

		Iterator(LindenmayerString& parent, int pos)
			: m_parent(parent), m_pos(pos) { }

		bool AtStart() {
			return m_pos <= -1;
		}

		bool AtEnd() {
			return (unsigned int)m_pos >= m_parent.m_symbols.size();
		}

		LindenmayerSymbol& operator*() {
			return m_parent.m_symbols[m_pos];
		}

		LindenmayerSymbol* operator->() {
			return &(m_parent.m_symbols[m_pos]);
		}

		Iterator operator++() {
			++m_pos;
			return *this;
		}

		Iterator operator--() {
			--m_pos;
			return *this;
		}

		bool operator==(Iterator& other) {
			return this->operator*().GetSymbol() == other.operator*().GetSymbol();
		}

		bool operator!=(Iterator& other) {
			return this->operator*().GetSymbol() != other.operator*().GetSymbol();
		}
	};
	
	void Add(LindenmayerSymbol symbol) {
		m_symbols.push_back(symbol);
	}

	void Add(LindenmayerString::Iterator& it) {
		m_symbols.push_back(*it);
	}

	void Add(LindenmayerString& str) {
		for (unsigned int i = 0; i < str.Size(); i++) {
			Add(str[i]);
		}
	}

	Iterator operator[](unsigned int index) {
		return Iterator(*this, index);
	}

	unsigned int Size() const {
		return m_symbols.size();
	}

	void Clear() {
		m_symbols.clear();
	}

	Iterator Begin() {
		return Iterator(*this, 0);
	}

	Iterator Last() {
		return Iterator(*this, m_symbols.size() - 1);
	}

	void swap(LindenmayerString& other) {
		std::swap(m_symbols, other.m_symbols);
	}
};

namespace {
	void swap(LindenmayerString& lhs, LindenmayerString& rhs) {
		lhs.swap(rhs);
	}
}