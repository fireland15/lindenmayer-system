#pragma once

#include <OpenMesh\Core\Mesh\TriMesh_ArrayKernelT.hh>

namespace fli {
	namespace geometry_generator {
		struct MeshTraits : public OpenMesh::DefaultTraits {
			typedef OpenMesh::Vec4f Color;

			VertexAttributes(OpenMesh::Attributes::Normal | OpenMesh::Attributes::Color);
			FaceAttributes(OpenMesh::Attributes::Normal | OpenMesh::Attributes::Color);
		};

		typedef OpenMesh::TriMesh_ArrayKernelT<MeshTraits> Mesh;
	}
}