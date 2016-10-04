#pragma once

#include "lindenmayer-symbol.h"

#include <vector>

class LindenmayerString {
private:
	std::vector<LindenmayerSymbol> m_symbols;
	
public:
	class Iterator {
	private:
		LindenmayerString& m_parent;
		int m_pos;

	public:
		Iterator(LindenmayerString& parent); // Defaults to begining
		Iterator(LindenmayerString& parent, int pos);
		bool AtStart();
		bool AtEnd();
		LindenmayerSymbol& operator*();
		LindenmayerSymbol* operator->();
		Iterator operator++();
		Iterator operator--();
		bool operator==(Iterator& other);
		bool operator!=(Iterator& other);
	};

	class ConstIterator {
	private:
		const LindenmayerString& mc_parent;
		int m_pos;

	public:
		ConstIterator(const LindenmayerString& parent, int pos);
		bool AtStart();
		bool AtEnd();
		const LindenmayerSymbol& operator*();
		const LindenmayerSymbol* operator->();
		ConstIterator operator++();
		ConstIterator operator--();
		bool operator==(ConstIterator& other);
		bool operator!=(ConstIterator& other);
	};

	LindenmayerString();
	LindenmayerString(std::initializer_list<LindenmayerSymbol> symbols);	
	void Add(LindenmayerSymbol symbol);
	void Add(LindenmayerString::Iterator& it);
	void Add(LindenmayerString& str);
	Iterator operator[](unsigned int index);
	size_t Size() const;
	void Clear();
	Iterator Begin();
	ConstIterator Begin() const;
	Iterator Last();
	ConstIterator Last() const;
	void swap(LindenmayerString& other);

private:
	LindenmayerString(std::vector<LindenmayerSymbol> symbols);
};

namespace {
	void swap(LindenmayerString& lhs, LindenmayerString& rhs) {
		lhs.swap(rhs);
	}
}