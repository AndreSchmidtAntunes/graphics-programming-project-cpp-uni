#include "GLExtras.h"

#include "Mesh.h"

#define DEFAULT_VERT_COLOUR Colour::Red

namespace GLExtras {

	void AddVertex(const Vector3& position) {
		glVertex3d((GLdouble)position.x, (GLdouble)position.y, (GLdouble)position.z);
	}

	void AddVertices(Vector3* points_array, const size_t length) {
		SetColour(DEFAULT_VERT_COLOUR);
		for (size_t i = 0; i < length; i++) {
			AddVertex(points_array[i]);
		}
	}

	void AddVerticesWithColours(const Vector3* vertices, const Colour* colours, const size_t length) {
		for (size_t i = 0; i < length; i++) {
			SetColour(colours ? colours[i] : DEFAULT_VERT_COLOUR);			
			AddVertex(vertices[i]);
		}
	}

	void SetColourHexRGBA(const size_t& Hex) {
		SetColour(Colour::Hex8(Hex));
	}

	void SetColourHexRGB(const size_t& Hex) {
		SetColour(ColourRGB::Hex6(Hex));
	}

	void SetColour(const float r, const float g, const float b, const float a) {
		SetColour(Colour(r, g, b, a));
	}

	void SetColour(const Colour& colour) {
		glColor4f(colour.r, colour.g, colour.b, colour.a);
	}
}