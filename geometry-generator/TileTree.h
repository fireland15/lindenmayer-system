#pragma once

#include <map>
#include <tuple>

#include "Graph.h"
#include "../glm/glm.hpp"
#include "Mesh.h"
#include "CrossSection.h"

typedef Graph<int, glm::vec3>::Node Node;

class TileTree {
private:
	Mesh* m_pMesh = nullptr;
	glm::vec3 m_referenceVector;
	Graph<int, glm::vec3> m_tree;
	std::map<std::shared_ptr<Node>, float> m_branchWidths;
	std::map<std::shared_ptr<Node>, CrossSection> m_crossSections;

public:
	TileTree(Graph<int, glm::vec3> tree)
		: m_tree(tree) { 
		m_pMesh = new Mesh;
		m_referenceVector = glm::vec3(1.0F, 0.0F, 0.0F);
	}

private:
	void Tile(std::shared_ptr<Node> pCurrent, glm::vec3 dir) { 
		int childCount = pCurrent->get_Children().size();

		if (childCount == 0) {
			// CloseTube(pMesh, pCurrent.CrossSection)
			CloseCrossSection(m_crossSections[pCurrent]);
		}
		else if (childCount == 1) {
			// MakeTube(pMesh, pCurrent.Parent.CrossSection, pCurrent.CrossSection)
			// Tile(pMesh, pCurrent.Child)
			std::shared_ptr<Node> child = pCurrent->get_Children().front();
			MakeTube(m_crossSections[pCurrent], pCurrent->get_Value(), child->get_Value(), m_branchWidths[child]);
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

	std::shared_ptr<Node> FindStraightestChild(const glm::vec3& dir, glm::vec3 fromPoint, std::list<std::shared_ptr<Node>> childrenPoints) { }
	CrossSection MakeCrossSection(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4) { }

	std::list<std::shared_ptr<Node>> FilterChildrenInQuadrant(int quadrant, glm::vec3 dir, std::list<std::shared_ptr<Node>> children) {
		glm::vec3 norm = glm::normalize(dir);
		glm::vec3 p = glm::normalize(FindPerpendicular(dir, m_referenceVector));
		glm::vec3 q = glm::normalize(FindPerpendicular(dir, p));

		for (std::shared_ptr<Node> child : children) {
			glm::vec3 proj = child->get_Value() - glm::dot(child->get_Value(), norm) * norm;
			float angleP = std::acos(glm::dot(glm::normalize(proj), glm::normalize(p)));
			float angleQ = std::acos(glm::dot(glm::normalize(proj), glm::normalize(q)));

			switch (quadrant) {
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			}
		}
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

		CrossSection cs;
		cs.vertices[0] = m_pMesh->add_vertex(OpenMesh::Vec3f(a.x, a.y, a.z));
		cs.vertices[1] = m_pMesh->add_vertex(OpenMesh::Vec3f(b.x, b.y, a.z));
		cs.vertices[2] = m_pMesh->add_vertex(OpenMesh::Vec3f(c.x, c.y, c.z));
		cs.vertices[3] = m_pMesh->add_vertex(OpenMesh::Vec3f(d.x, d.y, d.z));

		return cs;
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
};