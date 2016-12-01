#pragma once

#include <vector>
#include <memory>
#include <OpenMesh\Core\Mesh\PolyMesh_ArrayKernelT.hh>
#include "../glm/glm.hpp"

#include "BaseRecorder.h"
#include "EmptyRecorder.h"
#include "PointRecorder.h"
#include "Mesh.h"
#include "Enums.h"
#include "TileTree.h"

namespace fli {
	namespace geometry_generator {
		typedef Graph<float, glm::vec3>::Node Node;

		class RecordInterpreter {
		private:
			const float m_leafRadius = 0.5f;

		public:
			std::unique_ptr<Mesh> Interpret(std::shared_ptr<BaseRecorder> recorder, GeometryType geometryType = GeometryType::Points) {
				if (dynamic_cast<EmptyRecorder*>(recorder.get())) {
					return InterpretEmptyRecorder(static_cast<EmptyRecorder*>(recorder.get()));
				}
				else if (dynamic_cast<PointRecorder*>(recorder.get())) {
					return InterpretPointRecorderWithTriangles(static_cast<PointRecorder*>(recorder.get()));
				}
				else if (dynamic_cast<GraphRecorder*>(recorder.get())) {
					if (geometryType == GeometryType::Points) {
						return InterpretGraphRecorderPoints(static_cast<GraphRecorder*>(recorder.get()));
					}
					else if (geometryType == GeometryType::Tubes) {
						return InterpretGraphRecorderTubes(static_cast<GraphRecorder*>(recorder.get()));
					}
					else if (geometryType == GeometryType::Smooth) {
						return InterpretGraphRecorderSmooth(static_cast<GraphRecorder*>(recorder.get()));
					}
				}
				return std::unique_ptr<Mesh>(nullptr);
			}

		private:
			std::unique_ptr<Mesh> InterpretEmptyRecorder(EmptyRecorder* emptyRecorder) {
				return std::unique_ptr<Mesh>(new Mesh);
			}

			std::unique_ptr<Mesh> InterpretPointRecorder(PointRecorder* pointRecorder) {
				Mesh* mesh = new Mesh;

				for (TurtleState state : pointRecorder->GetRecords()) {
					glm::vec3 p = state.position;
					mesh->add_vertex(OpenMesh::Vec3f(p.x, p.y, p.z));
				}

				return std::unique_ptr<Mesh>(mesh);
			}

			std::unique_ptr<Mesh> InterpretPointRecorderWithTriangles(PointRecorder* pointRecorder) {
				float scale = 1.0f;
				glm::vec3 a(0.0f, -0.1f, 0.0f);
				glm::vec3 b(0.0f, 0.05f, 0.1f);
				glm::vec3 c(0.0f, 0.05f, -0.1f);

				Mesh* mesh = new Mesh;

				for (TurtleState state : pointRecorder->GetRecords()) {
					glm::vec3 p = state.position;
					glm::vec3 p_a = p + (scale * a);
					glm::vec3 p_b = p + (scale * b);
					glm::vec3 p_c = p + (scale * c);

					OpenMesh::VertexHandle h1 = mesh->add_vertex(OpenMesh::Vec3f(p_a.x, p_a.y, p_a.z));
					OpenMesh::VertexHandle h2 = mesh->add_vertex(OpenMesh::Vec3f(p_b.x, p_b.y, p_b.z));
					OpenMesh::VertexHandle h3 = mesh->add_vertex(OpenMesh::Vec3f(p_c.x, p_c.y, p_c.z));

					OpenMesh::FaceHandle f = mesh->add_face({ h1, h2, h3 });

					//scale -= 0.05f;
				}

				return std::unique_ptr<Mesh>(mesh);
			}

			std::unique_ptr<Mesh> InterpretGraphRecorderPoints(GraphRecorder* graphRecorder) {
				Mesh* mesh = new Mesh;

				Graph<float, glm::vec3> graph = graphRecorder->get_Graph();

				std::shared_ptr<Node> root = graph.get_RootNode();

				for (auto child : root->get_Children()) {
					DrawChild(mesh, child, root);
				}

				return std::unique_ptr<Mesh>(mesh);
			}

			std::unique_ptr<Mesh> InterpretGraphRecorderTubes(GraphRecorder* graphRecorder) {
				Mesh* mesh = new Mesh;

				Graph<float, glm::vec3> graph = graphRecorder->get_Graph();

				std::shared_ptr<Node> root = graph.get_RootNode();

				for (auto child : root->get_Children()) {
					DrawChild(mesh, child, root);
				}

				return std::unique_ptr<Mesh>(mesh);
			}

			std::unique_ptr<Mesh> InterpretGraphRecorderSmooth(GraphRecorder* graphRecorder) {
				TileTree tileTree(graphRecorder->get_Graph());
				return tileTree.Tile();
			}

			float DrawChild(Mesh* mesh, std::shared_ptr<Node> current, std::shared_ptr<Node> parent) {
				std::list<std::shared_ptr<Node>> children = current->get_Children();
				if (children.size() == 0) {
					MakeTubeBetweenPoints(mesh, current->get_Value(), parent->get_Value(), m_leafRadius);
					return m_leafRadius;
				}
				else {
					float accumulatedChildArea = 0.00f;
					for (auto child : children) {
						float childRadius = DrawChild(mesh, child, current);
						accumulatedChildArea += (M_PI * childRadius * childRadius);
					}
					float radius = std::sqrt(accumulatedChildArea / M_PI);
					MakeTubeBetweenPoints(mesh, current->get_Value(), parent->get_Value(), radius);
					return radius;
				}
			}

			void MakeTubeBetweenPoints(Mesh* mesh, glm::vec3 a, glm::vec3 b, float radius) {
				glm::vec3 dir = b - a;
				glm::vec3 ndir = glm::normalize(dir);

				glm::vec3 p = MakePerpendicularVector(ndir);
				glm::vec3 q = MakePerpendicularVector(ndir, p);

				glm::vec3 base[4];
				base[0] = p * radius + a;
				base[1] = q * radius + a;
				base[2] = -p * radius + a;
				base[3] = -q * radius + a;

				glm::vec3 top[4];
				top[0] = (p * radius) + b;
				top[1] = (q * radius) + b;
				top[2] = (-p * radius) + b;
				top[3] = (-q * radius) + b;

				OpenMesh::VertexHandle b0 = mesh->add_vertex(OpenMesh::Vec3f(base[0].x, base[0].y, base[0].z));
				OpenMesh::VertexHandle b1 = mesh->add_vertex(OpenMesh::Vec3f(base[1].x, base[1].y, base[1].z));
				OpenMesh::VertexHandle b2 = mesh->add_vertex(OpenMesh::Vec3f(base[2].x, base[2].y, base[2].z));
				OpenMesh::VertexHandle b3 = mesh->add_vertex(OpenMesh::Vec3f(base[3].x, base[3].y, base[3].z));

				OpenMesh::VertexHandle t0 = mesh->add_vertex(OpenMesh::Vec3f(top[0].x, top[0].y, top[0].z));
				OpenMesh::VertexHandle t1 = mesh->add_vertex(OpenMesh::Vec3f(top[1].x, top[1].y, top[1].z));
				OpenMesh::VertexHandle t2 = mesh->add_vertex(OpenMesh::Vec3f(top[2].x, top[2].y, top[2].z));
				OpenMesh::VertexHandle t3 = mesh->add_vertex(OpenMesh::Vec3f(top[3].x, top[3].y, top[3].z));

				mesh->add_face({ b0, b1, t0 });
				mesh->add_face({ t1, t0, b1 });

				mesh->add_face({ b1, b2, t1 });
				mesh->add_face({ t2, t1, b2 });

				mesh->add_face({ b2, b3, t2 });
				mesh->add_face({ t3, t2, b3 });

				mesh->add_face({ b3, b0, t3 });
				mesh->add_face({ t0, t3, b0 });
			}

			glm::vec3 MakePerpendicularVector(glm::vec3 a) {
				glm::vec3 arr[2];
				arr[0] = glm::vec3(a.z, a.z, -(a.x + a.y));
				arr[1] = glm::vec3(-(a.y + a.z), a.x, a.x);

				int index = ((a.z != 0) && (-a.x != a.y));
				return glm::normalize(arr[index]);
			}

			glm::vec3 MakePerpendicularVector(glm::vec3 a, glm::vec3 b) {
				return glm::normalize(glm::cross(a, b));
			}
		};
	}
}