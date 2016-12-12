#pragma once

#include "Mesh.h"
#include "Math.h"

namespace fli {
	namespace geometry_generator {
		struct CrossSection {
			CrossSection() { }

			CrossSection(Mesh* pMesh, glm::vec3 pos, glm::vec3 dir, glm::vec3 ref, float radius) {
				glm::vec3 projUp = glm::normalize(math::projectToPlane(dir, ref));
				glm::vec3 o = glm::normalize(glm::cross(dir, projUp));


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

				//AddQuadrantDirToMesh(pMesh, pos, quadrantDir[0], true);
				//AddQuadrantDirToMesh(pMesh, pos, quadrantDir[1]);
				//AddQuadrantDirToMesh(pMesh, pos, quadrantDir[2]);
				//AddQuadrantDirToMesh(pMesh, pos, quadrantDir[3]);
			}

			Mesh::VertexHandle vertices[4];
			glm::vec3 vertexPos[4];
			glm::vec3 quadrantDir[4];

			int closestQuadrant(glm::vec3 v) {
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

		private:
			void AddQuadrantDirToMesh(Mesh* pMesh, glm::vec3 pos, glm::vec3 dir, bool q = false) {
				glm::vec3 arrow[7] = {
					glm::vec3(3.0F, 0.0F, 0.0F), //point
					glm::vec3(2.5F, 0.0F, 0.5F),
					glm::vec3(2.55F, 0.0F, 0.15F),
					glm::vec3(2.0F, 0.0F, 0.15F),
					glm::vec3(2.0F, 0.0F, -0.15F),
					glm::vec3(2.55F, 0.0F, -0.15F),
					glm::vec3(2.5F, 0.0F, -0.5F)
				};

				Mesh::VertexHandle handle[7];

				glm::vec3 arrowDir(1.0F, 0.0F, 0.0F);

				float angle = std::acos(glm::dot(arrowDir, glm::normalize(dir)));
				glm::vec3 axis = glm::cross(arrowDir, dir);

				if (angle == NAN) {
					angle = 0.0F;
				}

				for (int i = 0; i < 7; i++) {
					if (q) {
						arrow[i] = arrow[i] * 3.0F;
					}

					if (arrowDir != dir) {
						arrow[i] = glm::rotate(arrow[i], angle, glm::normalize(axis)) + pos;
					}

					handle[i] = pMesh->add_vertex(OpenMesh::Vec3f(arrow[i].x, arrow[i].y, arrow[i].z));
				}

				pMesh->add_face(handle[0], handle[1], handle[2]);
				pMesh->add_face(handle[0], handle[5], handle[6]);
				pMesh->add_face(handle[0], handle[2], handle[6]);
				pMesh->add_face(handle[2], handle[3], handle[4]);
				pMesh->add_face(handle[2], handle[4], handle[5]);
			}
		};
	}
}