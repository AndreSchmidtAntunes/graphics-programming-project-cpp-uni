#pragma once

#include "Colour.h"
#include "GLLibs.h"
#include "Vector3.h"

enum MeshBuffer {
	VERTEX_BUFFER,
	COLOUR_BUFFER,
	MAX_BUFFER,
};

class Mesh
{
public:
	Mesh(void);
	~Mesh(void);

	virtual void Draw();
	static Mesh* GenerateTriangle();

protected:
	void BufferData();

	GLuint arrayObject;
	GLuint bufferObject[MAX_BUFFER];
	GLuint numVertices;
	GLuint type;

	Vector3* vertices;
	Colour* colours;
};

