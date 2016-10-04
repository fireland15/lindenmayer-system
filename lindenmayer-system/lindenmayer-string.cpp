#include "lindenmayer-string.h"

LindenmayerString::LindenmayerString() { }

LindenmayerString::LindenmayerString(std::initializer_list<LindenmayerSymbol> symbols) 
	: m_symbols(symbols) { }

LindenmayerString::LindenmayerString(std::vector<LindenmayerSymbol> symbols)
	: m_symbols(symbols) { }

void LindenmayerString::Add(LindenmayerSymbol symbol) {
	m_symbols.push_back(symbol);
}

void LindenmayerString::Add(LindenmayerString::Iterator& it) {
	m_symbols.push_back(*it);
}

void LindenmayerString::Add(LindenmayerString& str) {
	for (unsigned int i = 0; i < str.Size(); ++i) {
		Add(str[i]);
	}
}

LindenmayerString::Iterator LindenmayerString::operator[](unsigned int index) {
	return Iterator(*this, index);
}

LindenmayerString::Iterator LindenmayerString::Begin() {
	return Iterator(*this, 0);
}

LindenmayerString::ConstIterator LindenmayerString::Begin() const {
	return ConstIterator(*this, 0);
}

LindenmayerString::Iterator LindenmayerString::Last() {
	return Iterator(*this, (int) m_symbols.size() - 1);
}

LindenmayerString::ConstIterator LindenmayerString::Last() const {
	return ConstIterator(*this, (int) m_symbols.size() - 1);
}

size_t LindenmayerString::Size() const {
	return m_symbols.size();
}

void LindenmayerString::Clear() {
	m_symbols.clear();
}

void LindenmayerString::swap(LindenmayerString& other) {
	std::swap(m_symbols, other.m_symbols);
}

LindenmayerString::Iterator::Iterator(LindenmayerString& parent)
	: m_parent(parent), m_pos(0) { }

LindenmayerString::Iterator::Iterator(LindenmayerString& parent, int pos)
	: m_parent(parent), m_pos(pos) { }

bool LindenmayerString::Iterator::AtStart() {
	return m_pos <= -1;
}

bool LindenmayerString::Iterator::AtEnd() {
	return (unsigned int)m_pos >= m_parent.m_symbols.size();
}

LindenmayerSymbol& LindenmayerString::Iterator::operator*() {
	return m_parent.m_symbols[m_pos];
}

LindenmayerSymbol* LindenmayerString::Iterator::operator->() {
	return &(m_parent.m_symbols[m_pos]);
}

LindenmayerString::Iterator LindenmayerString::Iterator::operator++() {
	++m_pos;
	return *this;
}

LindenmayerString::Iterator LindenmayerString::Iterator::operator--() {
	--m_pos;
	return *this;
}

bool LindenmayerString::Iterator::operator==(Iterator& other) {
	return this->operator*().GetSymbol() == other.operator*().GetSymbol();
}

bool LindenmayerString::Iterator::operator!=(Iterator& other) {
	return this->operator*().GetSymbol() != other.operator*().GetSymbol();
}

LindenmayerString::ConstIterator::ConstIterator(const LindenmayerString & parent, int pos)
	: mc_parent(parent), m_pos(pos) { }

bool LindenmayerString::ConstIterator::AtStart() {
	return m_pos <= -1;
}

bool LindenmayerString::ConstIterator::AtEnd() {
	return (unsigned int)m_pos >= mc_parent.m_symbols.size();
}

const LindenmayerSymbol & LindenmayerString::ConstIterator::operator*() {
	return mc_parent.m_symbols[m_pos];
}

const LindenmayerSymbol * LindenmayerString::ConstIterator::operator->() {
	return &(mc_parent.m_symbols[m_pos]);
}

LindenmayerString::ConstIterator LindenmayerString::ConstIterator::operator++() {
	++m_pos;
	return *this;
}

LindenmayerString::ConstIterator LindenmayerString::ConstIterator::operator--() {
	--m_pos;
	return *this;
}

bool LindenmayerString::ConstIterator::operator==(ConstIterator & other) {
	return this->operator*().GetSymbol() == other.operator*().GetSymbol();

}

bool LindenmayerString::ConstIterator::operator!=(ConstIterator & other) {
	return this->operator*().GetSymbol() != other.operator*().GetSymbol();
}
