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
	Graph<int, glm::vec3> m_tree;
	std::map<std::shared_ptr<Node>, float> m_branchWidths;
	std::map<std::shared_ptr<Node>, CrossSection> m_crossSections;

public:
	TileTree(Graph<int, glm::vec3> tree)
		: m_tree(tree) { }

private:
	void Tile(Mesh* pMesh, std::shared_ptr<Node> pCurrent) { 
		int childCount = pCurrent->get_Children().size();

		if (childCount == 0) {
			// CloseTube(pMesh, pCurrent.CrossSection)
		}
		else if (childCount == 1) {
			// MakeTube(pMesh, pCurrent.Parent.CrossSection, pCurrent.CrossSection)
			// Tile(pMesh, pCurrent.Child)
		}
		else {
			// dir = pCurrent - pCurrent.Parent
			// Call TileJoint(pMesh, pCurrent, pCurrent.Children, dir)
		}
	}

	void TileJoint(Mesh* mesh, std::shared_ptr<Node> parentNode, std::list<std::shared_ptr<Node>> childrenNodes, const glm::vec3& dir) { 
		// straightestChild = FindStraightestChild(dir, parentNode, childrenNodes)
		// strChildDir =  straightestChild.Position - parentNode.Position
		// strChildCS = MakeCrossSection(straightestChild, strChildDir, m_branchWidths[straightestChild], refVec)
		// ChildrenInQ[0] = FilterChildrenInQuadrant(0, refVec, strChildDir, childrenNodes)
		// ChildrenInQ[1] = FilterChildrenInQuadrant(1, refVec, strChildDir, childrenNodes)
		// ChildrenInQ[2] = FilterChildrenInQuadrant(2, refVec, strChildDir, childrenNodes)
		// ChildrenInQ[3] = FilterChildrenInQuadrant(3, refVec, strChildDir, childrenNodes)

	}

	std::shared_ptr<Node> FindStraightestChild(const glm::vec3& dir, glm::vec3 fromPoint, std::list<std::shared_ptr<Node>> childrenPoints) { }
	CrossSection MakeCrossSection(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4) { }
	std::list<std::shared_ptr<Node>> FilterChildrenInQuadrant(int quadrant, glm::vec3 referenceVector, glm::vec3 dir, std::list<std::shared_ptr<Node>> children) { }

	// Make Geometry Functions
	void CloseCrossSection(Mesh* pMesh, const CrossSection& crossSection) { }
	CrossSection MakeCrossSection(std::shared_ptr<Node> node, glm::vec3 dir, float radius, glm::vec3 referenceVector) { }
	CrossSection MakeTube(Mesh* mesh, const CrossSection& baseCrossSection, const glm::vec3& fromPoint, const glm::vec3& toPoint, float endRadius, glm::vec3 referenceVector) { }
	void MakeTube(Mesh* mesh, const CrossSection& cs1, const CrossSection& cs2) { }
};