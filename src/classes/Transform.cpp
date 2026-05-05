#include "Transform.h"

#include "Mesh.h"

void Transform::Draw() const {
	if (_mesh && is_mesh_enabled)
		_mesh->DrawElements(_material, _texture);
}

