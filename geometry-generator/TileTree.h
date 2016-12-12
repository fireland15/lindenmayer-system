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
			std::map<std::shared_ptr<Node>, glm::vec3> m_directions;
			std::map<std::shared_ptr<Node>, glm::vec3> m_referenceVec;
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
					m_directions[rootNode] = m_upVector;
					DetermineDirection(rootNode);
					m_referenceVec[rootNode] = m_referenceVector;
					DetermineReferenceVectors(rootNode);
					DetermineCrossSections(rootNode, glm::vec3());

					Tile(rootNode);
					return std::unique_ptr<Mesh>(m_pMesh);
				}

				return nullptr;
			}

		private:
			void Tile(std::shared_ptr<Node> rootNode) {
				std::queue<std::shared_ptr<Node>> queue;
				queue.push(rootNode);

				//m_crossSections[rootNode] = MakeCrossSection(rootNode->get_Value(), m_directions[rootNode], m_referenceVec[rootNode], m_branchWidths[rootNode]);

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
						//m_crossSections[child] = MakeCrossSection(child->get_Value(), m_directions[child], m_referenceVec[child], m_branchWidths[child]);
						MakeTube(m_crossSections[node], m_crossSections[child]);
						queue.push(child);
					}
					else {
						TileJoint(node);
						for (auto child : children) {
							//m_crossSections[child] = MakeCrossSection(child->get_Value(), m_directions[child], m_referenceVec[child], m_branchWidths[child]);
							queue.push(child);
						}
					}
				}

				/*for (auto cs = m_crossSections.begin(); cs != m_crossSections.end(); cs++) {
					CloseCrossSection(cs->second);
				}*/
			}

			void TileJoint(std::shared_ptr<Node> parent) {
				// TODO: should be a set
				std::list<std::shared_ptr<Node>> children = parent->get_Children();
				std::shared_ptr<Node> strChild = FindStraightestChild(m_directions[parent], children);
				children.remove(strChild);

				std::list<std::shared_ptr<Node>> quadrantChildren[4];

				for (auto child : children) {
					quadrantChildren[m_crossSections[strChild].closestQuadrant(math::projectToPlane(m_directions[strChild], m_directions[child]))].push_back(child);
				}

				for (int i = 0; i < 4; i++) {
					if (quadrantChildren[i].empty()) {
						CloseQuadrant(m_crossSections[parent], m_crossSections[strChild], i);
					}
					else {
						Mesh::VertexHandle vertices[4] = {
							m_crossSections[strChild].vertices[(i + 1) % 4],
							m_crossSections[strChild].vertices[i],
							m_crossSections[parent].vertices[i],
							m_crossSections[parent].vertices[(i + 1) % 4]
						};

						TileJoint(parent, quadrantChildren[i], i, strChild, vertices);
					}
				}
			}

			void TileJoint(std::shared_ptr<Node> parent, std::list<std::shared_ptr<Node>> children, int fromQuadrant, std::shared_ptr<Node> connectTo, Mesh::VertexHandle vertices[4]) {
				std::shared_ptr<Node> strChild = FindStraightestChild(m_directions[parent], children);
				children.remove(strChild);

				std::list<std::shared_ptr<Node>> quadrantChildren[4];

				for (auto child : children) {
					quadrantChildren[m_crossSections[strChild].closestQuadrant(math::projectToPlane(m_directions[strChild], m_directions[child]))].push_back(child);
				}

				for (int i = 0; i < 4; i++) {
					Mesh::VertexHandle vertex[4];
					if (i == fromQuadrant) {
						vertex[0] = m_crossSections[strChild].vertices[(i + 1) % 4];
						vertex[1] = m_crossSections[strChild].vertices[i];
						vertex[2] = vertices[2];
						vertex[3] = vertices[3];
					}
					else if (i == (fromQuadrant + 1) % 4) {
						vertex[0] = m_crossSections[strChild].vertices[(i + 1) % 4];
						vertex[1] = m_crossSections[strChild].vertices[i];
						vertex[2] = vertices[3];
						vertex[3] = vertices[0];
					}
					else if (i == (fromQuadrant - 1) % 4) {
						vertex[0] = m_crossSections[strChild].vertices[(i + 1) % 4];
						vertex[1] = m_crossSections[strChild].vertices[i];
						vertex[2] = vertices[1];
						vertex[3] = vertices[2];
					}
					else {
						continue;
					}

					if (quadrantChildren[i].empty() && i != (fromQuadrant + 2) % 4) {
						ClosePatch(vertex);
					}
					else {
						TileJoint(parent, quadrantChildren[i], i, strChild, vertex);
					}
				}

				MakeTransitionPatch(m_crossSections[connectTo], fromQuadrant, m_crossSections[strChild], (fromQuadrant + 2) % 4);
			}

			void MakeTransitionPatch(CrossSection cs1, int quadrant1, CrossSection cs2, int quadrant2) {
				if (quadrant1 == 1 && quadrant2 == 3) {
					m_pMesh->add_face(cs1.vertices[2], cs1.vertices[1], cs2.vertices[0], cs2.vertices[3]);
					//m_pMesh->add_face(cs1.vertices[1], cs2.vertices[3], cs2.vertices[0]);
					//m_pMesh->add_face(cs1.vertices[1], cs2.vertices[3], cs1.vertices[2]);
				}
				else if (quadrant1 == 3 && quadrant2 == 1) {
					m_pMesh->add_face(cs1.vertices[0], cs1.vertices[3], cs2.vertices[2], cs2.vertices[1]);
					//m_pMesh->add_face(cs1.vertices[0], cs2.vertices[2], cs2.vertices[1]);
					//m_pMesh->add_face(cs1.vertices[0], cs2.vertices[2], cs1.vertices[3]);
				}
				else if (quadrant1 == 0 && quadrant2 == 2) {
					m_pMesh->add_face(cs1.vertices[1], cs1.vertices[0], cs2.vertices[3], cs2.vertices[2]);
				}
				else if (quadrant1 == 2 && quadrant2 == 0) {
					m_pMesh->add_face(cs1.vertices[3], cs1.vertices[2], cs2.vertices[1], cs2.vertices[0]);
				}
			}

			void CloseQuadrant(CrossSection cs1, CrossSection cs2, int quadrant) {
				m_pMesh->add_face(cs1.vertices[quadrant], cs1.vertices[(quadrant + 1) % 4], cs2.vertices[(quadrant + 1) % 4], cs2.vertices[quadrant]);
			}

			void ClosePatch(Mesh::VertexHandle v[4]) {
				m_pMesh->add_face(v[0], v[1], v[2], v[3]);
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

			void DetermineDirection(std::shared_ptr<Node> node) {
				if (node == nullptr)
					return;
				if (node->get_Children().size() == 0)
					return;
				for (std::shared_ptr<Node> child : node->get_Children()) {
					m_directions[child] = math::direction(child->get_Value(), node->get_Value());
					DetermineDirection(child);
				}
			}

			void DetermineReferenceVectors(std::shared_ptr<Node> node) {
				if (node == nullptr)
					return;
				if (node->get_Children().size() == 0)
					return;
				for (std::shared_ptr<Node> child : node->get_Children()) {
					m_referenceVec[child] = glm::normalize(math::projectToPlane(glm::normalize(m_directions[child]), glm::normalize(m_referenceVec[node])));
					DetermineReferenceVectors(child);
				}
			}

			void DetermineCrossSections(std::shared_ptr<Node> node, glm::vec3 ref) {
				if (node == nullptr) 
					return;

				std::queue<std::shared_ptr<Node>> queue;
				queue.push(node);

				while (!queue.empty()) {
					std::shared_ptr<Node> current = queue.front();
					queue.pop();

					m_crossSections[current] = MakeCrossSection(current->get_Value(), m_directions[current], m_referenceVec[current], m_branchWidths[current]);
					
					for (auto child : current->get_Children()) {
						queue.push(child);
					}
				}
			}

			std::shared_ptr<Node> FindStraightestChild(const glm::vec3& dir, std::list<std::shared_ptr<Node>> childrenPoints) {
 				std::shared_ptr<Node> straightestChild = nullptr;
				float maxDot = 0;

				for (std::shared_ptr<Node> child : childrenPoints) {
					float dot = glm::dot(m_directions[child], glm::normalize(dir));

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
				m_pMesh->add_face(crossSection.vertices[0], crossSection.vertices[1], crossSection.vertices[2], crossSection.vertices[3]);
				/*m_pMesh->add_face(crossSection.vertices[0], crossSection.vertices[1], crossSection.vertices[2]);
				m_pMesh->add_face(crossSection.vertices[0], crossSection.vertices[2], crossSection.vertices[3]);*/
			}

			CrossSection MakeCrossSection(glm::vec3 pos, glm::vec3 dir, glm::vec3 ref, float radius) {
				return CrossSection(m_pMesh, pos, dir, ref, radius);
			}

			CrossSection MakeCrossSection(Mesh::VertexHandle v0, Mesh::VertexHandle v1, Mesh::VertexHandle v2, Mesh::VertexHandle v3) {
				CrossSection cs;
				cs.vertices[0] = v0;
				cs.vertices[1] = v1;
				cs.vertices[2] = v2;
				cs.vertices[3] = v3;
				return cs;
			}

			//CrossSection MakeTube(const CrossSection& baseCrossSection, const glm::vec3& fromPoint, const glm::vec3& toPoint, float radius) {
			//	glm::vec3 dir = toPoint - fromPoint;
			//	CrossSection endCrossSection = MakeCrossSection(toPoint, dir, radius);
			//	MakeTube(baseCrossSection, endCrossSection);
			//	return endCrossSection;
			//}

			void MakeTube(const CrossSection& cs1, const CrossSection& cs2) {
				m_pMesh->add_face(cs1.vertices[0], cs1.vertices[1], cs2.vertices[1], cs2.vertices[0]);
				m_pMesh->add_face(cs1.vertices[1], cs1.vertices[2], cs2.vertices[2], cs2.vertices[1]);
				m_pMesh->add_face(cs1.vertices[2], cs1.vertices[3], cs2.vertices[3], cs2.vertices[2]);
				m_pMesh->add_face(cs1.vertices[3], cs1.vertices[0], cs2.vertices[0], cs2.vertices[3]);
				//m_pMesh->add_face(cs1.vertices[0], cs1.vertices[1], cs2.vertices[1]);
				//m_pMesh->add_face(cs1.vertices[0], cs2.vertices[1], cs2.vertices[0]);
				//
				//m_pMesh->add_face(cs1.vertices[1], cs1.vertices[2], cs2.vertices[2]);
				//m_pMesh->add_face(cs1.vertices[1], cs2.vertices[2], cs2.vertices[1]);
				//
				//m_pMesh->add_face(cs1.vertices[2], cs1.vertices[3], cs2.vertices[3]);
				//m_pMesh->add_face(cs1.vertices[2], cs2.vertices[3], cs2.vertices[2]);
				//
				//m_pMesh->add_face(cs1.vertices[3], cs1.vertices[0], cs2.vertices[0]);
				//m_pMesh->add_face(cs1.vertices[3], cs2.vertices[0], cs2.vertices[3]);
			}

			glm::vec3 FindPerpendicular(glm::vec3 p, glm::vec3 q) {
				return glm::normalize(glm::cross(p, q));
			}
		};
	}
}