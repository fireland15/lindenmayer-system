#include "value-node.h"

ValueNode::ValueNode(float value)
	: m_value(value) { }

float ValueNode::operator()() {
	return m_value;
}

void ValueNode::Delete() {
	return;
}

unsigned int ValueNode::NumChildren() { 
	return 0; 
}