#include "variable-node.h"

VariableNode::VariableNode(std::string symbol)
	:m_isSet(false), m_symbol(symbol) { }

void VariableNode::SetValue(float value) {
	m_value = value;
	m_isSet = true;
}

float VariableNode::operator()() {
	if (!m_isSet)
		throw ValueNotSetException(m_symbol);
	return m_value;
}

void VariableNode::Delete() {
	return;
}

unsigned int VariableNode::NumChildren() { 
	return 0; 
}