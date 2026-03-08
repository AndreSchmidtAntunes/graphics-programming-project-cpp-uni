#include "customGLExtras.h"

#include "common.h"

namespace VertexWrapper {

	void AddVertex(const Vector3& position) {
		glVertex3d((GLdouble)position.x, (GLdouble)position.y, (GLdouble)position.z);
	}

	void AddVertecies(Vector3* points_array, int length) {
		for (int i = 0; i < length; i++) {
			VertexWrapper::AddVertex((points_array[i]));
		}
	}

	void AddVertecies(float* points, int length) {

		if (length % 3 == 0) 
		for (int i = 0; i < length; i += 3) {
			glVertex3d((GLdouble)points[0], (GLdouble)points[i + 1], (GLdouble)points[i + 2]);
		}

		else {
			throw std::range_error("The float array's length was not a multiple of 3. 3 floats are required per point (x, y and z positions).");
		}
	}
}

