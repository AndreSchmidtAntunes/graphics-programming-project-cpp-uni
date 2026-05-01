#pragma once

#include "Mesh.h"
#include "Transform.h"
#include "GLExtras.h"
#include <vector>

class Scene {
public:

	// the overarching parent transform of the scene
	Transform* const root = new Transform(this);

	Scene(void)	{ }
	~Scene(void) { 
		delete root; 
	}

	inline void Clear(const size_t child_index) const {
		for (size_t i = 0; i < root->children.size(); i++)
			root->DestroyChild(i);
	}

	inline Transform* getChild(const size_t index) const {
		return root->getChild(index);
	} 

	inline const std::vector<Transform*> getAllChildren() const {
		return root->getChildren();
	}

	void DrawFamilyHierarchy(Transform* const parent) const {
		glPushMatrix();

		GLExtras::PerformTransformation(parent->local_position, parent->local_rotation, parent->local_scale);

		if (parent->mesh != nullptr && parent->is_mesh_enabled)
			parent->mesh->DrawElements();

		for (auto child : parent->getChildren()) {
			DrawFamilyHierarchy(child);
		}

		glPopMatrix();
	}

	void Draw(Camera* const camera) const {
		glPushMatrix();

		glLoadIdentity();

		GLExtras::LookAt(camera->position, camera->position - camera->forward, camera->up);

		//GLExtras::PerformTransformation(-camera->position, -camera->rotation, Vector3::One);

		for (auto child : root->getChildren()) {
			DrawFamilyHierarchy(child);
		}
		glPopMatrix();
	}
};