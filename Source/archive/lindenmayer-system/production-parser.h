#pragma once

#include <string>
#include <algorithm>

class ProductionStringParser {
private:
	std::string m_preContext;
	std::string m_postContext;
	char m_symbol;
	std::string m_result;

public:
	ProductionStringParser(const std::string& str);
	void Parse(const std::string& str);
	std::string ExtractPreContext(std::string& str);
	std::string ExtractPostContext(std::string& str);
	char ExtractSymbol(std::string& str);
	std::string GetPreContext();
	std::string GetPostContext();
	char GetSymbol();
	std::string GetResult();

private:
	char ExtractSymbolNoContext(std::string& str);
	char ExtractSymbolPreContext(std::string& str);
	char ExtractSymbolPostContext(std::string& str);
	char ExtractSymbolFullContext(std::string& str);
};
