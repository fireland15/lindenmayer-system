#include "production-parser.h"

ProductionStringParser::ProductionStringParser(const std::string& str) {
	Parse(str);
}

void ProductionStringParser::Parse(const std::string& str) {
	std::string prodRules = str.substr(0, str.find_first_of(':'));
	prodRules.erase(std::remove_if(prodRules.begin(), prodRules.end(), isspace), prodRules.end());

	m_preContext = ExtractPreContext(prodRules);
	m_postContext = ExtractPostContext(prodRules);
	m_symbol = ExtractSymbol(prodRules);
	m_result = str.substr(str.find_first_of(':') + 1, str.size());
	m_result.erase(std::remove_if(m_result.begin(), m_result.end(), isspace), m_result.end());
}

std::string ProductionStringParser::ExtractPreContext(std::string& str) {
	size_t preIndex = str.find_first_of('<');
	if (preIndex == std::string::npos)
		return std::string();

	return str.substr(0, preIndex);
}

std::string ProductionStringParser::ExtractPostContext(std::string& str) {
	size_t postIndex = str.find_first_of('>');
	if (postIndex == std::string::npos)
		return std::string();

	return str.substr(postIndex + 1, str.size());
}

char ProductionStringParser::ExtractSymbol(std::string& str) {
	size_t preIndex = str.find_first_of('<');
	size_t postIndex = str.find_first_of('>');
	size_t npos = std::string::npos;

	if (preIndex == npos && postIndex == npos)
		return ExtractSymbolNoContext(str);
	else if (preIndex == npos && postIndex != npos)
		return ExtractSymbolPostContext(str);
	else if (preIndex != npos && postIndex == npos)
		return ExtractSymbolPreContext(str);
	else
		return ExtractSymbolFullContext(str);

}

std::string ProductionStringParser::GetPreContext() { return m_preContext; }

std::string ProductionStringParser::GetPostContext() { return m_postContext; }

char ProductionStringParser::GetSymbol() { return m_symbol; }

std::string ProductionStringParser::GetResult() { return m_result; }

char ProductionStringParser::ExtractSymbolNoContext(std::string& str) {
	return str[0];
}

char ProductionStringParser::ExtractSymbolPreContext(std::string& str) {
	return str[str.find_first_of('<') + 1];
}

char ProductionStringParser::ExtractSymbolPostContext(std::string& str) {
	return str[0];
}

char ProductionStringParser::ExtractSymbolFullContext(std::string& str) {
	return str[str.find_first_of('<') + 1];
}