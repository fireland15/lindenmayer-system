#pragma once

#include <map>
#include <tuple>

#include "Graph.h"
#include "../glm/glm.hpp"
#include "Mesh.h"
#include "CrossSection.h"

#ifndef M_PI
#define M_PI 3.14159265368979323846
#endif

#ifndef M_PI_2
#define M_PI_2 M_PI / 2
#endif

typedef Graph<float, glm::vec3>::Node Node;

class TileTree {
private:
	Mesh* m_pMesh = nullptr;
	glm::vec3 m_referenceVector;
	Graph<float, glm::vec3> m_tree;
	std::map<std::shared_ptr<Node>, float> m_branchWidths;
	std::map<std::shared_ptr<Node>, CrossSection> m_crossSections;

public:
	TileTree(Graph<float, glm::vec3> tree)
		: m_tree(tree) { 
		m_pMesh = new Mesh;
		m_referenceVector = glm::vec3(1.0F, 0.0F, 0.0F);
	}

	std::unique_ptr<Mesh> Tile() {
		std::shared_ptr<Node> rootNode = m_tree.get_RootNode();

		if (rootNode != nullptr) {
			Tile(rootNode, glm::vec3(0.0F, 1.0F, 0.0F));
			return std::unique_ptr<Mesh>(m_pMesh);
		}

		return nullptr;
	}

private:
	void Tile(std::shared_ptr<Node> pCurrent, glm::vec3 dir) { 
		int childCount = pCurrent->get_Children().size();

		if (childCount == 0) {
			// CloseTube(pMesh, pCurrent.CrossSection)
			if (m_crossSections.count(pCurrent) == 0) {

			}
			else {
				CloseCrossSection(m_crossSections[pCurrent]);
			}
		}
		else if (childCount == 1) {
			// MakeTube(pMesh, pCurrent.Parent.CrossSection, pCurrent.CrossSection)
			// Tile(pMesh, pCurrent.Child)
			std::shared_ptr<Node> child = pCurrent->get_Children().front();
			if (m_crossSections.count(pCurrent) == 0) {
				MakeTube(MakeCrossSection(pCurrent->get_Value(), glm::vec3(0.0F, 1.0F, 0.0F), 1.0F), pCurrent->get_Value(), child->get_Value(), 1.0F);
			}
			else {
				MakeTube(m_crossSections[pCurrent], pCurrent->get_Value(), child->get_Value(), 1.0F);
			}
			Tile(child, glm::normalize(child->get_Value() - pCurrent->get_Value()));
		}
		else {
			// Call TileJoint(pCurrent, pCurrent.Children, dir)
			TileJoint(pCurrent, dir);
		}
	}

	void TileJoint(std::shared_ptr<Node> parentNode, const glm::vec3& dir) {
		TileJoint(parentNode, parentNode->get_Children(), m_crossSections[parentNode], dir);
	}

	void TileJoint(std::shared_ptr<Node> parentNode, std::list<std::shared_ptr<Node>> childrenNodes, const CrossSection parentCrossSection, const glm::vec3& dir) { 
		// straightestChild = FindStraightestChild(dir, parentNode, childrenNodes)
		// strChildDir =  straightestChild.Position - parentNode.Position
		// strChildCS = MakeCrossSection(straightestChild, strChildDir, m_branchWidths[straightestChild], refVec)
		// ChildrenInQ[0] = FilterChildrenInQuadrant(0, refVec, strChildDir, childrenNodes)
		// ChildrenInQ[1] = FilterChildrenInQuadrant(1, refVec, strChildDir, childrenNodes)
		// ChildrenInQ[2] = FilterChildrenInQuadrant(2, refVec, strChildDir, childrenNodes)
		// ChildrenInQ[3] = FilterChildrenInQuadrant(3, refVec, strChildDir, childrenNodes)

		// QuadrantCS[0] = MakeCrossSection(strChildCS[0], strChildCS[1], parentCrossSection[0], parentCrossSection[1]);
		// QuadrantCS[1] = MakeCrossSection(strChildCS[1], strChildCS[2], parentCrossSection[1], parentCrossSection[2]);
		// QuadrantCS[2] = MakeCrossSection(strChildCS[2], strChildCS[3], parentCrossSection[2], parentCrossSection[3]);
		// QuadrantCS[3] = MakeCrossSection(strChildCS[3], strChildCS[0], parentCrossSection[3], parentCrossSection[0]);

		// for (int i = 0; i < 4; i++)
		//     if (ChildreninQ[i].size() == 0)
		//		   CloseCrossSection(QuadrantCS[i]);
		//     else
		//		   TileJoint(parentNode, ChildrenInQ[i], QuadrantCS[i], strChildDir);
		//     Tile(strChild, strChildDir)

		std::shared_ptr<Node> strChild = FindStraightestChild(dir, parentNode->get_Value(), childrenNodes);
		glm::vec3 strChildDir = strChild->get_Value() - parentNode->get_Value();
		CrossSection strChildCs = MakeCrossSection(strChild->get_Value(), strChildDir, m_branchWidths[strChild]);

		std::list<std::shared_ptr<Node>> ChildrenInQuadrant[4];
		for (int i = 0; i < 4; i++) {
			ChildrenInQuadrant[i] = FilterChildrenInQuadrant(i, strChildDir, childrenNodes);
		}

		CrossSection QuadrantCs[4];
		for (int i = 0; i < 4; i++) {
			QuadrantCs[i] = MakeCrossSection(strChildCs.vertices[0], strChildCs.vertices[1], parentCrossSection.vertices[0], parentCrossSection.vertices[1]);
		}

		for (int i = 0; i < 4; i++) {
			if (ChildrenInQuadrant[i].size() == 0) {
				CloseCrossSection(QuadrantCs[i]);
			}
			else {
				TileJoint(parentNode, ChildrenInQuadrant[i], QuadrantCs[i], strChildDir);
			}
			Tile(strChild, strChildDir);
		}
	}

	std::shared_ptr<Node> FindStraightestChild(const glm::vec3& dir, glm::vec3 fromPoint, std::list<std::shared_ptr<Node>> childrenPoints) { 
		std::shared_ptr<Node> straightestChild = nullptr;
		float closestChildAngle = M_PI;

		for (std::shared_ptr<Node> child : childrenPoints) {
			float angle = FindAngle(child->get_Value() - fromPoint, dir);

			if (angle < closestChildAngle) {
				straightestChild = child;
				closestChildAngle = angle;
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
		return cs;
	}

	std::list<std::shared_ptr<Node>> FilterChildrenInQuadrant(int quadrant, glm::vec3 dir, std::list<std::shared_ptr<Node>> children) {
		glm::vec3 norm = glm::normalize(dir);
		glm::vec3 p = glm::normalize(FindPerpendicular(dir, m_referenceVector));
		glm::vec3 q = glm::normalize(FindPerpendicular(dir, p));

		std::list<std::shared_ptr<Node>> filteredChildren;

		for (std::shared_ptr<Node> child : children) {
			glm::vec3 proj = child->get_Value() - glm::dot(child->get_Value(), norm) * norm;
			float angleP = FindAngle(proj, p);
			float angleQ = FindAngle(proj, q);

			switch (quadrant) {
			case 0:
				if (angleP < M_PI_2 && angleQ < M_PI_2) {
					filteredChildren.push_back(child);
				}
				break;
			case 1:
				if (angleP > M_PI_2 && angleQ < M_PI_2) {
					filteredChildren.push_back(child);
				}
				break;
			case 2:
				if (angleP > M_PI_2 && angleQ > M_PI_2) {
					filteredChildren.push_back(child);
				}
				break;
			case 3:
				if (angleP < M_PI_2 && angleQ > M_PI_2) {
					filteredChildren.push_back(child);
				}
				break;
			}
		}

		return filteredChildren;
	}

	// Make Geometry Functions
	void CloseCrossSection(const CrossSection& crossSection) { 
		m_pMesh->add_face(crossSection.vertices[0], crossSection.vertices[1], crossSection.vertices[2]);
		m_pMesh->add_face(crossSection.vertices[0], crossSection.vertices[2], crossSection.vertices[3]);
	}

	CrossSection MakeCrossSection(const glm::vec3 point, glm::vec3 dir, float radius) { 
		glm::vec3 p0 = FindPerpendicular(dir, m_referenceVector);
		glm::vec3 p1 = FindPerpendicular(dir, p0);

		glm::vec3 a = point + p1 * radius;
		glm::vec3 b = point + p0 * radius;
		glm::vec3 c = point - p1 * radius;
		glm::vec3 d = point - p0 * radius;

		return MakeCrossSection(m_pMesh->add_vertex(OpenMesh::Vec3f(a.x, a.y, a.z)),
								m_pMesh->add_vertex(OpenMesh::Vec3f(b.x, b.y, a.z)),
								m_pMesh->add_vertex(OpenMesh::Vec3f(c.x, c.y, c.z)),
								m_pMesh->add_vertex(OpenMesh::Vec3f(d.x, d.y, d.z)));
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
		m_pMesh->add_face(cs1.vertices[0], cs1.vertices[1], cs2.vertices[1]);
		m_pMesh->add_face(cs1.vertices[0], cs2.vertices[1], cs2.vertices[0]);

		m_pMesh->add_face(cs1.vertices[1], cs1.vertices[2], cs2.vertices[2]);
		m_pMesh->add_face(cs1.vertices[1], cs2.vertices[2], cs2.vertices[1]);

		m_pMesh->add_face(cs1.vertices[2], cs1.vertices[3], cs2.vertices[3]);
		m_pMesh->add_face(cs1.vertices[2], cs2.vertices[3], cs2.vertices[2]);

		m_pMesh->add_face(cs1.vertices[3], cs1.vertices[0], cs2.vertices[0]);
		m_pMesh->add_face(cs1.vertices[3], cs2.vertices[0], cs2.vertices[3]);
	}

	glm::vec3 FindPerpendicular(glm::vec3 p, glm::vec3 q) {
		return glm::normalize(glm::cross(p, q));
	}

	float FindAngle(glm::vec3 p, glm::vec3 q) {
		return std::acos(glm::dot(glm::normalize(p), glm::normalize(q)));
	}
};