#pragma once

#include <map>
#include <tuple>
#include <queue>

#include "Graph.h"
#include "../glm/glm.hpp"
#include "Mesh.h"
#include "CrossSection.h"
#include "Math.h"

namespace fli {
	namespace geometry_generator {
		typedef Graph<float, glm::vec3>::Node Node;

		class TileTree {
		private:
			Mesh* m_pMesh = nullptr;
			glm::vec3 m_referenceVector;
			Graph<float, glm::vec3> m_tree;
			std::map<std::shared_ptr<Node>, float> m_branchWidths;
			std::map<std::shared_ptr<Node>, CrossSection> m_crossSections;
			float m_minBranchRadius = 0.5F;
			glm::vec3 m_upVector = glm::vec3(0.0F, 1.0F, 0.0F);

		public:
			TileTree(Graph<float, glm::vec3> tree)
				: m_tree(tree) {
				m_pMesh = new Mesh;
				m_referenceVector = glm::normalize(glm::vec3(1.0F, 0.0F, 1.0F));
			}

			std::unique_ptr<Mesh> Tile() {
				std::shared_ptr<Node> rootNode = m_tree.get_RootNode();

				if (rootNode != nullptr) {
					DetermineBranchWidth(rootNode, m_minBranchRadius);
					Tile(rootNode);
					return std::unique_ptr<Mesh>(m_pMesh);
				}

				return nullptr;
			}

		private:
			void Tile(std::shared_ptr<Node> rootNode) {
				std::queue<std::shared_ptr<Node>> queue;
				queue.push(rootNode);

				m_crossSections[rootNode] = MakeCrossSection(rootNode->get_Value(), m_upVector, m_branchWidths[rootNode]);

				while (!queue.empty()) {
					std::shared_ptr<Node> node = queue.front();
					queue.pop();

					std::list<std::shared_ptr<Node>> children = node->get_Children();

					if (children.size() == 0) {
						CloseCrossSection(m_crossSections[node]);
					}
					else if (children.size() == 1) {
						auto child = children.front();
						glm::vec3 dir = math::direction(child->get_Value(), node->get_Value());
						m_crossSections[child] = MakeCrossSection(child->get_Value(), dir, m_branchWidths[child]);
						MakeTube(m_crossSections[node], m_crossSections[child]);
						queue.push(child);
					}
					else {
						for (auto child : children) {
							m_crossSections[child] = MakeCrossSection(child->get_Value(), math::direction(child->get_Value(), node->get_Value()), m_branchWidths[child]);
							queue.push(child);
						}
					}
				}
			}

			float DetermineBranchWidth(std::shared_ptr<Node> node, float leafWidth) {
				if (node->get_Children().empty()) {
					m_branchWidths[node] = leafWidth;
					return leafWidth;
				}

				float squareSumArea = 0.0F;
				for (auto child : node->get_Children()) {
					float childWidth = DetermineBranchWidth(child, leafWidth);
					squareSumArea += (M_PI * childWidth * childWidth);
				}
				float radius = std::sqrt(squareSumArea / M_PI);
				m_branchWidths[node] = radius;
				return radius;
			}

			std::shared_ptr<Node> FindStraightestChild(const glm::vec3& dir, glm::vec3 fromPoint, std::list<std::shared_ptr<Node>> childrenPoints) {
 				std::shared_ptr<Node> straightestChild = nullptr;
				float maxDot = 0;

				for (std::shared_ptr<Node> child : childrenPoints) {
					float dot = glm::dot(math::direction(child->get_Value(), fromPoint), glm::normalize(dir));

					if (dot > maxDot) {
						straightestChild = child;
						maxDot = dot;
					}
				}

				return straightestChild;
			}

			CrossSection MakeCrossSection(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4) {
				CrossSection cs;
				cs.vertices[0] = m_pMesh->add_vertex(OpenMesh::Vec3f(p1.x, p1.y, p1.z));
				cs.vertices[1] = m_pMesh->add_vertex(OpenMesh::Vec3f(p2.x, p2.y, p2.z));
				cs.vertices[2] = m_pMesh->add_vertex(OpenMesh::Vec3f(p3.x, p3.y, p3.z));
				cs.vertices[3] = m_pMesh->add_vertex(OpenMesh::Vec3f(p4.x, p4.y, p4.z));

				cs.vertexPos[0] = p1;
				cs.vertexPos[1] = p2;
				cs.vertexPos[2] = p3;
				cs.vertexPos[3] = p4;

				return cs;
			}

			std::list<std::shared_ptr<Node>> FilterChildrenInQuadrant(int quadrant, glm::vec3 dir, glm::vec3 fromPoint, std::list<std::shared_ptr<Node>> children) {
				glm::vec3 norm = glm::normalize(dir);
				glm::vec3 p = glm::normalize(FindPerpendicular(dir, m_referenceVector));
				glm::vec3 q = glm::normalize(FindPerpendicular(dir, p));

				std::list<std::shared_ptr<Node>> filteredChildren;

				for (std::shared_ptr<Node> child : children) {
					glm::vec3 childDir = math::direction(child->get_Value(), fromPoint);
					glm::vec3 proj = glm::normalize(childDir - glm::dot(childDir, norm) * norm);
					float angleP = math::vectorAngleDegrees(proj, p);
					float angleQ = math::vectorAngleDegrees(proj, q);

					switch (quadrant) {
					case 0:
						if (angleP < 90.0F && angleQ < 90.0F) {
							filteredChildren.push_back(child);
						}
						break;
					case 1:
						if (angleP > 90.0F && angleQ < 90.0F) {
							filteredChildren.push_back(child);
						}
						break;
					case 2:
						if (angleP > 90.0F && angleQ > 90.0F) {
							filteredChildren.push_back(child);
						}
						break;
					case 3:
						if (angleP < 90.0F && angleQ > 90.0F) {
							filteredChildren.push_back(child);
						}
						break;
					}
				}

				return filteredChildren;
			}

			// Make Geometry Functions
			void CloseCrossSection(const CrossSection& crossSection) {
				m_pMesh->add_face(crossSection.vertices[0], crossSection.vertices[2], crossSection.vertices[1]);
				m_pMesh->add_face(crossSection.vertices[0], crossSection.vertices[3], crossSection.vertices[2]);
			}

			CrossSection MakeCrossSection(const glm::vec3 point, glm::vec3 dir, float radius) {
				glm::vec3 p0 = FindPerpendicular(dir, m_referenceVector);
				glm::vec3 p1 = FindPerpendicular(dir, p0);

				glm::vec3 a = point + p1 * radius;
				glm::vec3 b = point + p0 * radius;
				glm::vec3 c = point - p1 * radius;
				glm::vec3 d = point - p0 * radius;

				return MakeCrossSection(a, b, c, d);
			}

			CrossSection MakeCrossSection(Mesh::VertexHandle v0, Mesh::VertexHandle v1, Mesh::VertexHandle v2, Mesh::VertexHandle v3) {
				CrossSection cs;
				cs.vertices[0] = v0;
				cs.vertices[1] = v1;
				cs.vertices[2] = v2;
				cs.vertices[3] = v3;
				return cs;
			}

			CrossSection MakeTube(const CrossSection& baseCrossSection, const glm::vec3& fromPoint, const glm::vec3& toPoint, float radius) {
				glm::vec3 dir = toPoint - fromPoint;
				CrossSection endCrossSection = MakeCrossSection(toPoint, dir, radius);
				MakeTube(baseCrossSection, endCrossSection);
				return endCrossSection;
			}

			void MakeTube(const CrossSection& cs1, const CrossSection& cs2) {
				m_pMesh->add_face(cs1.vertices[1], cs1.vertices[0], cs2.vertices[1]);
				m_pMesh->add_face(cs1.vertices[0], cs2.vertices[0], cs2.vertices[1]);

				m_pMesh->add_face(cs1.vertices[2], cs1.vertices[1], cs2.vertices[2]);
				m_pMesh->add_face(cs1.vertices[1], cs2.vertices[1], cs2.vertices[2]);

				m_pMesh->add_face(cs1.vertices[3], cs1.vertices[2], cs2.vertices[3]);
				m_pMesh->add_face(cs1.vertices[2], cs2.vertices[2], cs2.vertices[3]);

				m_pMesh->add_face(cs1.vertices[0], cs1.vertices[3], cs2.vertices[0]);
				m_pMesh->add_face(cs1.vertices[3], cs2.vertices[3], cs2.vertices[0]);
			}

			glm::vec3 FindPerpendicular(glm::vec3 p, glm::vec3 q) {
				return glm::normalize(glm::cross(p, q));
			}
		};
	}
}