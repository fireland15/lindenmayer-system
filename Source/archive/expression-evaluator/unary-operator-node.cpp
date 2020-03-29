#include "unary-operator-node.h"

UnaryOperatorNode::UnaryOperatorNode(std::function<float(float)> operation)
	:m_operation(operation) { }

float UnaryOperatorNode::operator()() {
	return m_operation((*m_child)());
}

void UnaryOperatorNode::Delete() {
	m_child->Delete();
	delete m_child;
}

unsigned int UnaryOperatorNode::NumChildren() {
	return 1; 
}

void UnaryOperatorNode::SetChild(ExpressionNode* child, unsigned int i) {
	m_child = child;
}