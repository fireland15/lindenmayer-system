#pragma once

#include "../glm/gtx/rotate_vector.hpp"

#include "Mesh.h"
#include "Math.h"

namespace fli {
	namespace geometry_generator {
		struct CrossSection {
			Mesh::VertexHandle vertices[4];

		private:
			glm::vec3 quadrantDir[4];

		public:
			CrossSection();
			CrossSection(Mesh* pMesh, glm::vec3 pos, glm::vec3 dir, glm::vec3 ref, float radius);
			int ClosestQuadrant(glm::vec3 v);
		};
	}
}