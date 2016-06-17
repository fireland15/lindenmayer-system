#pragma once

#include <string>

#include "lindenmayer-string.h"

class StrToLstrConverter {
public:
	LindenmayerString* operator()(std::string& str) {
		LindenmayerString* lstr = new LindenmayerString;

		for (char c : str) {
			lstr->Add(LindenmayerSymbol(c));
		}

		return lstr;
	}
};