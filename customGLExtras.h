#pragma once

#include "GLLibs.h"
#include "Vector3.h"

namespace VertexWrapper {
	void AddVertex(const Vector3& position);
	void AddVertecies(Vector3* points_array, int length);
}