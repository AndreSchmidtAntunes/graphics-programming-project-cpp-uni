#include "Mesh.h"

Mesh::Mesh(void) {
	for (int i = 0; i < MAX_BUFFER; ++i) {
		bufferObject[i] = 0;
	}
	
	arrayObject = glGenLists(1);

	numVertices = 0;
	vertices = NULL;
	colours = NULL;
	type = GL_TRIANGLES;
	/// replace creating a new vertex buffer with smthn else
}

Mesh::~Mesh(void) {
	glDeleteLists(arrayObject, 1);
	glDeleteLists(*bufferObject, MAX_BUFFER);
	delete[] vertices;
	delete[] colours;
}

//Mesh* Mesh::GenerateTriangle() {
//	Mesh* mesh = new Mesh();
//	mesh->numVertices = 3;
//
//	mesh->vertices = new Vector3[mesh->numVertices];
//	mesh->vertices[0] = Vector3(0.0, 0.5, 0.0);
//	mesh->vertices[1] = Vector3(0.5, -0.5, 0.0);
//	mesh->vertices[2] = Vector3(-0.5, -0.5, 0.0);
//
//	mesh->colours = new Colour[mesh->numVertices];
//	mesh->colours[0] = Colour(1.0, 0.0, 0.0, 1.0);
//	mesh->colours[1] = Colour(0.0, 1.0, 0.0, 1.0);
//	mesh->colours[2] = Colour(0.0, 0.0, 1.0, 1.0);
//
//	mesh->BufferData();
//
//	return mesh;
//}

void Mesh::BufferData() {

}

void Mesh::Draw() {

}