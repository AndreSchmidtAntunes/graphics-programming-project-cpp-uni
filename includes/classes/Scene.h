#pragma once

#include <vector>

class Camera;
class Transform;

class Scene {

public:

	// the overarching parent transform of the scene
	Transform* const root;

	Transform* focused_transform = nullptr;

	Scene(void);
	~Scene(void);

	void Clear(const size_t child_index) const;

	Transform* const getChild(const size_t index) const;

	const std::vector<Transform*> getAllChildren() const;

	std::vector<Transform*> getAllChildren();

	void DrawFamilyHierarchy(Transform* const parent) const;

	void Draw(Camera* const camera) const;

	const int GetNextAvailableObjectID() const;
};