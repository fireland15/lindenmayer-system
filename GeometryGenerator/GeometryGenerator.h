#pragma once

#include <vector>

#include "../lindenmayer-system/production-rule.h"

using namespace System;

namespace GeometryGenerator {

	public ref class PlantGenerator
	{


	private:
		std::vector<ProductionRule>* rules = new std::vector<ProductionRule>();
	};
}
