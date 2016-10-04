#pragma once

#include <vector>
#include <memory>
#include <OpenMesh\Core\Mesh\PolyMesh_ArrayKernelT.hh>
#include "../glm/glm.hpp"

#include "BaseRecorder.h"
#include "EmptyRecorder.h"
#include "PointRecorder.h"
#include "Mesh.h"

class RecordInterpreter { 
public: 
	std::unique_ptr<Mesh> Interpret(std::shared_ptr<BaseRecorder> recorder) {
		if (dynamic_cast<EmptyRecorder*>(recorder.get())) {
			return InterpretEmptyRecorder(static_cast<EmptyRecorder*>(recorder.get()));
		}
		else if (dynamic_cast<PointRecorder*>(recorder.get())) {
			return InterpretPointRecorderWithTriangles(static_cast<PointRecorder*>(recorder.get()));
		}
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
};