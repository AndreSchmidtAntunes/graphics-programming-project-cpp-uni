#pragma once

#include <vector>

class Camera;
class Transform;

class Scene {

	Camera* _camera = nullptr;

public:

	// the overarching parent transform of the scene
	Transform* const root;

	inline Camera* const getCamera() const { return _camera; }
	void setCamera(Camera* const camera);

	Scene(void);
	~Scene(void);

	void Clear(const size_t child_index) const;

	Transform* const getChild(const size_t index) const;

	const std::vector<Transform*> getAllChildren() const;

	std::vector<Transform*> getAllChildren();

	const int GetNextAvailableObjectID() const;
};