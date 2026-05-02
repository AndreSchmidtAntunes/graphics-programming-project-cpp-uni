#include "Scene.h"

#include "Camera.h"
#include "GLExtras.h"
#include "Mesh.h"
#include "Transform.h"

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

void Scene::Draw(Camera* const camera) const {
	glPushMatrix();
	glLoadIdentity();

	GLExtras::LookAt(camera->position, camera->position - camera->forward, camera->up);

	for (auto child : root->getChildren()) {
		DrawFamilyHierarchy(child);
	}
	glPopMatrix();
}
