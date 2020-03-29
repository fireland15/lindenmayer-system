#pragma once

#include <string>
#include <stdexcept>

// Exceptions
class ValueNotSetException : public std::runtime_error {
	std::string m_undefinedSymbol;
public:
	ValueNotSetException(std::string symbol);

	virtual const char* what();

	const std::string GetUndefinedSymbol();
};

class ParseException : public std::runtime_error {
private:
	std::string m_message;

public:
	ParseException(std::string message);

	virtual const char* what();
};