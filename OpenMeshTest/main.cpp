#define _USE_MATH_DEFINES

#include <OpenMesh\Core\Mesh\PolyMesh_ArrayKernelT.hh>
#include <OpenMesh\Core\IO\MeshIO.hh>
#include <iostream>
#include <cmath>

typedef OpenMesh::PolyMesh_ArrayKernelT<> Mesh;


int main() {
	Mesh mesh;

	mesh.add_vertex(Mesh::Point(0.0f, 0.0f, 0.0f));
	mesh.add_vertex(Mesh::Point(0.0f, 0.0f, 0.0f));
	mesh.add_vertex(Mesh::Point(0.0f, 0.0f, 0.0f));
	mesh.add_vertex(Mesh::Point(0.0f, 0.0f, 0.0f));
	mesh.add_vertex(Mesh::Point(0.0f, 0.0f, 0.0f));
	mesh.add_vertex(Mesh::Point(0.0f, 0.0f, 0.0f));

	try
	{
		if (!OpenMesh::IO::write_mesh(mesh, "output.obj"))
		{
			std::cerr << "Cannot write mesh to file 'output.obj'" << std::endl;
			return 1;
		}
	}
	catch (std::exception& x)
	{
		std::cerr << x.what() << std::endl;
		return 1;
	}

	return 0;
}