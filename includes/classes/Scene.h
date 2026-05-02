#pragma once

#include <vector>

class Transform;
class Camera;

class Scene {
public:

	// the overarching parent transform of the scene
	Transform* const root;

	Scene(void);
	~Scene(void);

	void Clear(const size_t child_index) const;

	Transform* const getChild(const size_t index) const;

	const std::vector<Transform*> getAllChildren() const;

	std::vector<Transform*> getAllChildren();

	void DrawFamilyHierarchy(Transform* const parent) const;

	void Draw(Camera* const camera) const;
};