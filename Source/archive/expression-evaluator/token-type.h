#pragma once

enum class TokenType : unsigned int {
	Value,
	Identifier,
	Operator,
	LParen,
	RParen
};