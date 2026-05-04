#include "Scene.h"

#include "Camera.h"
#include "GLExtras.h"
#include "Mesh.h"
#include "Transform.h"
#include "Vector3.h"

Scene::Scene(void) : root(new Transform(this)) {}
Scene::~Scene(void) { delete root; }

void Scene::Clear(const size_t child_index) const {
	for (size_t i = 0; i < root->children.size(); i++)
		root->DestroyChild(i);
}

Transform* const Scene::getChild(const size_t index) const {
	return root->getChild(index);
}

const std::vector<Transform*> Scene::getAllChildren() const {
	return root->getChildren();
}

std::vector<Transform*> Scene::getAllChildren() {
	return root->getChildren();
}

void Scene::DrawFamilyHierarchy(Transform* const parent) const {
	glPushMatrix();

	GLExtras::PerformTransformation(parent->local_position, parent->local_rotation, parent->local_scale);

	if (parent->mesh != nullptr && parent->is_mesh_enabled)
		parent->mesh->DrawElements(parent->material, parent->texture);

	for (auto child : parent->getChildren()) {
		DrawFamilyHierarchy(child);
	}
	glPopMatrix();
}
#include <iostream>
void Scene::Draw(Camera* const camera) const {
	glPushMatrix();
	glLoadIdentity();

	if ((focused_transform != nullptr) && (focused_transform->scene == this) && (focused_transform != root)) {
		GLExtras::LookAt(camera->position, focused_transform->getWorldPosition(), camera->up);

		/// TODO: Broken view and cant turn off yet
	}
	else
		GLExtras::LookAt(camera->position, camera->position - camera->forward, camera->up);


	for (auto child : root->getChildren()) {
		DrawFamilyHierarchy(child);
	}


	glPopMatrix();
}

const int GetLowestAvailableID(const Transform* const root, int& lowest_unused_id) {
	if (root->getSceneTransformID() == lowest_unused_id)
		lowest_unused_id++;

	for (auto child : root->getChildren()) {
		GetLowestAvailableID(child, lowest_unused_id);
	}
	return lowest_unused_id;
}

const int Scene::GetNextAvailableObjectID() const {
	int lowest = 0;
	return GetLowestAvailableID(root, lowest);
}
