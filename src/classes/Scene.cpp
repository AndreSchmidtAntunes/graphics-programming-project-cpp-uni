#include "Scene.h"

#include "Transform.h"
#include "Vector3.h"
#include "Camera.h"

void Scene::setCamera(Camera* const camera) {
	if (_camera)
		_camera->_scene = nullptr;
	_camera = camera;
}

Scene::Scene(void) : root(new Basic_Transform(this)) {}
Scene::~Scene(void) { delete root; }

void Scene::Clear(const size_t child_index) const {
	for (size_t i = 0; i < root->_children.size(); i++)
		root->DestroyChild(i);
}

Basic_Transform* const Scene::getChild(const size_t index) const {
	return root->getChild(index);
}

const std::vector<Basic_Transform*> Scene::getAllChildren() const {
	return root->getChildren();
}

std::vector<Basic_Transform*> Scene::getAllChildren() {
	return root->getChildren();
}

const int GetLowestAvailableID(const Basic_Transform* const root, int& lowest_unused_id) {
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
