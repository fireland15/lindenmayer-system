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
	ProductionStringParser(const std::string& str) {
		Parse(str);
	}

	void Parse(const std::string& str) {
		std::string prodRules = str.substr(0, str.find_first_of(':'));
		prodRules.erase(std::remove_if(prodRules.begin(), prodRules.end(), isspace), prodRules.end());

		m_preContext = ExtractPreContext(prodRules);
		m_postContext = ExtractPostContext(prodRules);
		m_symbol = ExtractSymbol(prodRules);
		m_result = str.substr(str.find_first_of(':') + 1, str.size());
		m_result.erase(std::remove_if(m_result.begin(), m_result.end(), isspace), m_result.end());
	}

	std::string ExtractPreContext(std::string& str) {
		size_t preIndex = str.find_first_of('<');
		if (preIndex == std::string::npos)
			return std::string();

		return str.substr(0, preIndex);
	}

	std::string ExtractPostContext(std::string& str) {
		size_t postIndex = str.find_first_of('>');
		if (postIndex == std::string::npos)
			return std::string();

		return str.substr(postIndex + 1, str.size());
	}

	char ExtractSymbol(std::string& str) {
		size_t preIndex = str.find_first_of('<');
		size_t postIndex = str.find_first_of('>');

		if (preIndex == std::string::npos)
			preIndex = 0;
		if (postIndex == std::string::npos)
			postIndex = str.size();

		return str.substr(preIndex + 1, (postIndex - 1) - (preIndex))[0];
	}

	std::string GetPreContext() { return m_preContext; }
	std::string GetPostContext() { return m_postContext; }
	char GetSymbol() { return m_symbol; }
	std::string GetResult() { return m_result; }
};
