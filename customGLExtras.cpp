#include "customGLExtras.h"

#include "common.h"

namespace GLExtras {

	void AddVertex(const Vector3& position) {
		glVertex3d((GLdouble)position.x, (GLdouble)position.y, (GLdouble)position.z);
	}

	void AddVertices(Vector3* points_array, int length) {
		for (int i = 0; i < length; i++) {
			AddVertex((points_array[i]));
		}
	}

	void AddVerticesWithColours(Vector3* vertices, Colour* colours, int length) {
		for (int i = 0; i < length; i++) {
			SetColour(colours[i]);
			AddVertex(vertices[i]);
		}
	}

	void AddPolygon(const Poly& polygon) {
		glBegin(GL_POLYGON);
		{
			AddVerticesWithColours(polygon.verts, polygon.colours, polygon.vert_count);
		}
		glEnd();
	}

	void AddPolygons(Poly* polygons, int length) {
		for (int p = 0; p < length; p++)
			AddPolygon(polygons[p]);
	}

	void SetColourHexRGBA(const uint32& Hex) {
		SetColour(Colour::HexRGBAToColour(Hex));
	}

	void SetColourHexRGB(const uint32& Hex) {
		SetColour(Colour::HexRGBToColour(Hex));
	}

	void SetColour(const short& r, const short& g, const short& b, const short& a) {
		SetColour(Colour(r, g, b, a));
	}

	void SetColour(const Colour& colour) {
		glColor4f(colour.r, colour.g, colour.b, colour.a);
	}
}