#include "Model.h"

#include "Mesh.h"

void Model::Draw() const {
	if (_mesh && is_mesh_enabled)
		_mesh->DrawElements(_material, _texture);
}

