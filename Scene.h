#pragma once

#include <vector>
#include "Transform.h"

class Scene {

	Transform* const root = new Transform(this);

public:

	Transform* const getRootTransform() const {
		return root;
	}

	Scene(void) { }
	~Scene(void) { delete root; }

	inline void InsertChild(Transform* child, size_t index) {
		child->setParent(root, index);
	}

	inline void InsertChild(Transform* child) {
		child->setParent(root);
	}

	inline void DestroyChild(size_t child_index) {
		root->DestroyChild(child_index);
	}

	inline Transform* getChild(size_t index) const {
		return root->getChild(index);
	} 

	inline const std::vector<Transform*> getAllChildren() const {
		return root->getAllChildren();
	}
};