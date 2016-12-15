#include "CrossSection.h"

namespace fli {
	namespace geometry_generator {
		CrossSection::CrossSection() { }

		CrossSection::CrossSection(Mesh* pMesh, glm::vec3 pos, glm::vec3 dir, glm::vec3 ref, float radius) {
			glm::vec3 projUp = glm::normalize(math::projectToPlane(dir, ref));
			glm::vec3 o = glm::normalize(glm::cross(dir, projUp));

			glm::vec3 vertexPos[4];
			vertexPos[0] = pos + projUp * radius;
			vertexPos[1] = pos + o * radius;
			vertexPos[2] = pos - projUp * radius;
			vertexPos[3] = pos - o * radius;

			vertices[0] = pMesh->add_vertex(OpenMesh::Vec3f(vertexPos[0].x, vertexPos[0].y, vertexPos[0].z));
			vertices[1] = pMesh->add_vertex(OpenMesh::Vec3f(vertexPos[1].x, vertexPos[1].y, vertexPos[1].z));
			vertices[2] = pMesh->add_vertex(OpenMesh::Vec3f(vertexPos[2].x, vertexPos[2].y, vertexPos[2].z));
			vertices[3] = pMesh->add_vertex(OpenMesh::Vec3f(vertexPos[3].x, vertexPos[3].y, vertexPos[3].z));

			quadrantDir[0] = glm::normalize(glm::rotate(ref, glm::radians(45.0F), glm::normalize(dir)));
			quadrantDir[1] = glm::normalize(glm::rotate(ref, glm::radians(135.0F), glm::normalize(dir)));
			quadrantDir[2] = glm::normalize(glm::rotate(ref, glm::radians(225.0F), glm::normalize(dir)));
			quadrantDir[3] = glm::normalize(glm::rotate(ref, glm::radians(315.0F), glm::normalize(dir)));
		}

		int CrossSection::ClosestQuadrant(glm::vec3 v) {
			int closest = -1;
			float maxDot = FLT_MIN;

			for (int i = 0; i < 4; i++) {
				float dot = glm::dot(glm::normalize(v), quadrantDir[i]);
				if (dot > maxDot) {
					maxDot = dot;
					closest = i;
				}
			}

			return closest;
		}
	}
}