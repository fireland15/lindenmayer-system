#pragma once

#include "../glm/glm.hpp"

#ifndef M_PI
#define M_PI 3.14159265368979323846
#endif

#ifndef M_PI_2
#define M_PI_2 M_PI / 2
#endif

#ifndef M_PI_3
#define M_PI_3 M_PI / 3
#endif

#ifndef M_PI_4
#define M_PI_4 M_PI / 4
#endif

#ifndef M_PI_6
#define M_PI_6 M_PI / 6
#endif

namespace fli {
	namespace geometry_generator {
		namespace math {
			// TODO: add xml comments to document the requirement for a and b to be normalized.
			inline float vectorAngleRadians(glm::vec3 a, glm::vec3 b) {
				if (a == b) {
					return 0.00F;
				}
				return std::acos(glm::dot(a, b));
			}

			// TODO: add xml comments to document the requirement for a and b to be normalized.
			inline float vectorAngleDegrees(glm::vec3 a, glm::vec3 b) {
				if (a == b) {
					return 0.00F;
				}
				return glm::degrees(std::acos(glm::dot(a, b)));
			}

			inline glm::vec3 makeDirection(glm::vec3 to, glm::vec3 from) {
				return glm::normalize(to - from);
			}
		}
	}
}