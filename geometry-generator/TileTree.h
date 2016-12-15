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
			TileTree(Graph<float, glm::vec3> tree);

			std::unique_ptr<Mesh> Tile();

			void set_branchEndRadius(float radius);

			void set_referenceVector(glm::vec3 reference);

		private:
			void Tile(std::shared_ptr<Node> rootNode);

			void TileJoint(std::shared_ptr<Node> parent);

			void 
				TileJoint(
					std::shared_ptr<Node> parent, 
					std::list<std::shared_ptr<Node>> children, 
					int fromQuadrant, 
					std::shared_ptr<Node> connectTo, 
					Mesh::VertexHandle vertices[4]);

			std::shared_ptr<Node> 
				FindStraightestChild(
					const glm::vec3& dir, 
					std::list<std::shared_ptr<Node>> childrenPoints);

			std::list<std::shared_ptr<Node>> 
				FilterChildrenInQuadrant(
					int quadrant, 
					glm::vec3 dir, 
					glm::vec3 fromPoint, 
					std::list<std::shared_ptr<Node>> children);

			CrossSection 
				MakeCrossSection(
					glm::vec3 pos, 
					glm::vec3 dir, 
					glm::vec3 ref, 
					float radius);

			/**************************************************************************
			** Functions to add features to mesh
			***************************************************************************/
			void CloseCrossSection(const CrossSection& crossSection);

			void MakeTube(const CrossSection& cs1, const CrossSection& cs2);
			
			void MakeTransitionPatch(CrossSection cs1, int quadrant1, CrossSection cs2, int quadrant2);

			void CloseQuadrant(CrossSection cs1, CrossSection cs2, int quadrant);

			void ClosePatch(Mesh::VertexHandle v[4]);

			/**************************************************************************
			** Functions to calculate tree metadata
			***************************************************************************/
			float DetermineBranchWidth(std::shared_ptr<Node> node, float leafWidth);

			void DetermineDirection(std::shared_ptr<Node> node);

			void DetermineReferenceVectors(std::shared_ptr<Node> node);

			void DetermineCrossSections(std::shared_ptr<Node> node, glm::vec3 ref);
		};
	}
}