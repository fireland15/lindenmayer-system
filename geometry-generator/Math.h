#pragma once

#include "../glm/glm.hpp"

#ifndef M_PI
#define M_PI 3.14159265368979323846
#endif

#ifndef M_PI_2
#define M_PI_2 M_PI / 2
#endif

#ifndef M_PI_4
#define M_PI_4 M_PI / 4
#endif

namespace fli {
	namespace geometry_generator {
		namespace math {
			// TODO: add xml comments to document the requirement for a and b to be normalized.
			float vectorAngleRadians(glm::vec3 a, glm::vec3 b) {
				return std::acos(glm::dot(a, b));
			}

			// TODO: add xml comments to document the requirement for a and b to be normalized.
			float vectorAngleDegrees(glm::vec3 a, glm::vec3 b) {
				return glm::degrees(std::acos(glm::dot(a, b)));
			}
		}
	}
}