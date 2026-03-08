#pragma once

#include <vector>
#include "Vector3.h"

class Transform
{
public:

	inline void setPosition(Vector3 position);
	inline void setRotation(Vector3 position);
	inline void setScale(Vector3 position);

	void setParent(Transform*, int index, bool keep_transform);

	inline Vector3& getPosition();
	inline Vector3& getRotation();
	inline Vector3& getScale();

	inline int getChildIndex();

	Vector3 getWorldScale();
	Vector3 getWorldRotation();
	Vector3 getWorldPosition();

	/// <summary>
	/// Assign a function to run when this transform has changed.
	/// </summary>
	/// <param name="callback">A function which takes 3 Vector3 parameters as references (Vector3& position, Vector3& rotation, Vector3& scale).</param>
	void SetOnChangedFunc(void (*callback)(Vector3, Vector3, Vector3));

	/// <summary>
	/// Assign the function to run when this transform's position has changed.
	/// </summary>
	/// <param name="callback">A function which takes a Vector3 parameter as reference (Vector3& position).</param>
	void SetOnPositionChangedFunc(void (*callback)(Vector3));

	/// <summary>
	/// Assign the function to run when this transform's rotation has changed.
	/// </summary>
	/// <param name="callback">A function which takes a Vector3 parameter as reference (Vector3& rotation).</param>
	void SetOnRotationChangedFunc(void (*callback)(Vector3));

	/// <summary>
	/// Assign the function to run when this transform's scale has changed.
	/// </summary>
	/// <param name="callback">A function which takes a Vector3 parameter as reference (Vector3& scale).</param>
	void SetOnScaleChangedFunc(void (*callback)(Vector3));

protected:

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Transform* parent;
	int child_index;

	int child_count;
	//Transform** children;
	std::vector<Transform*> children;
	void (*anyChangedFunc)(Vector3, Vector3, Vector3);
	void (*posChangedFunc)(Vector3);
	void (*rotChangedFunc)(Vector3);
	void (*scaleChangedFunc)(Vector3);

	bool is_root;
	static Transform* root_transform;
};

