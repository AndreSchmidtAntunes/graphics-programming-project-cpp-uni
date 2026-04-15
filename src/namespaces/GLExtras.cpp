#include "GLExtras.h"

#include "Mesh.h"
#include "GLLibs.h"


#define DEFAULT_VERT_COLOUR Colour::RED

namespace GLExtras {

	void AddVertex(const Vector3& position) {
		glVertex3d((GLdouble)position.x, (GLdouble)position.y, (GLdouble)position.z);
	}

	void AddVertices(Vector3* points_array, const uint length) {
		SetColour(DEFAULT_VERT_COLOUR);
		for (uint i = 0; i < length; i++) {
			for (uint dim = 0; i < 3; i++) {
				AddVertex((points_array[i][dim])); // x to z
			}
		}
	}

	void AddVerticesWithColours(const Vector3* vertices, const Colour* colours, const uint length) {
		for (uint i = 0; i < length; i++) {
			SetColour(colours ? colours[i] : DEFAULT_VERT_COLOUR);			
			AddVertex(vertices[i]);
		}
	}

	//void AddMesh(const Mesh& mesh) {
	//	AddPolygons(mesh.polygons, mesh.polygons_count, mesh.vertices);
	//}

	void SetColourHexRGBA(const uint& Hex) {
		SetColour(Colour::Hex6(Hex));
	}

	void SetColourHexRGB(const uint& Hex) {
		SetColour(Colour::HexRGBToColour(Hex));
	}

	void SetColour(const float r, const float g, const float b, const float a) {
		SetColour(Colour(r, g, b, a));
	}

	void SetColour(const Colour& colour) {
		glColor4f(colour.r, colour.g, colour.b, colour.a);
	}
}