#include "Exceptions.h"

ValueNotSetException::ValueNotSetException(std::string symbol)
	: std::runtime_error("value undefined"), m_undefinedSymbol(symbol) { }

const char* ValueNotSetException::what() {
	return  (m_undefinedSymbol + " does not have a value assigned.").c_str();
}

const std::string ValueNotSetException::GetUndefinedSymbol() { 
	return m_undefinedSymbol; 
}

ParseException::ParseException(std::string message)
	: m_message(message), std::runtime_error(message) { }

const char* ParseException::what() {
	return m_message.c_str();
}
