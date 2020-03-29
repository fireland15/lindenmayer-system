#pragma once

enum class Associativity { left, right };

enum class Precedence { lowest, low, mid, high, highest };

enum class OperatorType : unsigned int {
	neg,
	add,
	sub,
	mul,
	div,
	eq, // equal
	neq, // not equal
	gt, // greater than
	lt, // less than
	geq, // greater than or equal
	leq // less than or equal
};
