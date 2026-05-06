#include "GLExtras.h"

#include "Mesh.h"

#define DEFAULT_VERT_COLOUR Colour::Red

static const double PI = 3.141592653589793;
static const double PHI = 1.570796326794897;
static const double RAD2DEG = 57.29577951308232;
static const double DEG2RAD = 0.017453292519943;

namespace GLExtras {

	void AddVertex(const Vector3& position) {
		glVertex3f(position.x, position.y, position.z);
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

	void PerformTransformation(const Vector3& position, const Quaternion& rotation, const Vector3& scale) {

		glTranslatef(position.x, position.y, position.z);

		Vector3 euler_rot = rotation.ToEuler();

		glRotatef(2 * acos(rotation.w) * RAD2DEG, rotation.x, rotation.y, rotation.z);

		//glRotatef(euler_rot.x * RAD2DEG, 1, 0, 0);
		//glRotatef(euler_rot.y * RAD2DEG, 0, 1, 0);
		//glRotatef(euler_rot.z * RAD2DEG, 0, 0, 1);

		glScalef(scale.x, scale.y, scale.z);
	}

	void LookAt(const Vector3& eye, const Vector3& target, const Vector3& up) {
		gluLookAt(
			eye.x, eye.y, eye.z,  // eye
			target.x, target.y, target.z,  // target  position
			up.x, up.y, up.z // up
		);
	}
}