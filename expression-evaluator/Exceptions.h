#pragma once

#include <string>
#include <stdexcept>

// Exceptions
class ValueNotSetException : public std::runtime_error {
	std::string m_undefinedSymbol;
public:
	ValueNotSetException(std::string symbol)
		: std::runtime_error("value undefined"), m_undefinedSymbol(symbol) {

	}

	virtual const char* what() {
		return  (m_undefinedSymbol + " does not have a value assigned.").c_str();
	}

	const std::string GetUndefinedSymbol() { return m_undefinedSymbol; }
};

class ParseException : public std::runtime_error {
private:
	std::string m_message;

public:
	ParseException(std::string message)
		: m_message(message), std::runtime_error(message) { }

	virtual const char* what() {
		return m_message.c_str();
	}
};