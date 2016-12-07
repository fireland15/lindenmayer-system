#pragma once

#include "Mesh.h"

namespace fli {
	namespace geometry_generator {
		struct CrossSection {
			CrossSection(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, float radius) {
				glm::vec3 projUp = glm::normalize(math::projectToPlane(dir, up));
				glm::vec3 o = glm::normalize(glm::cross(dir, projUp));


				vertexPos[0] = pos + projUp * radius;
				vertexPos[1] = pos + o * radius;
				vertexPos[2] = pos - projUp * radius;
				vertexPos[3] = pos - o * radius;
			}

			Mesh::VertexHandle vertices[4];
			glm::vec3 vertexPos[4];
			glm::vec3 reference;
		};
	}
}