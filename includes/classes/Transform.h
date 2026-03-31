#pragma once

#include <vector>
#include "Vector3.h"

template <class T = double>
class Transform
{

public:

	static_assert(std::is_floating_point<T>::value,
		"class T can only be a floating point type, as it is the type used for 3D calculations. (E.g: float, double, half)");

	inline void setPosition(Vector3<T> position);
	inline void setRotation(Vector3<T> position);
	inline void setScale(Vector3<T> position);

	void setParent(Transform* parent, int index, bool keep_transform = false);

	inline Vector3<T>& getPosition();
	inline Vector3<T>& getRotation();
	inline Vector3<T>& getScale();

	inline int getChildIndex();

	Vector3<T> getWorldScale();
	Vector3<T> getWorldRotation();
	Vector3<T> getWorldPosition();

	/// <summary>
	/// Assign a function to run when this transform has changed.
	/// </summary>
	/// <param name="callback">A function which takes 3 Vector3 parameters as references (Vector3<T>& position, Vector3<T>& rotation, Vector3<T>& scale).</param>
	void SetOnChangedFunc(void (*callback)(Vector3<T>, Vector3<T>, Vector3<T>));

	/// <summary>
	/// Assign the function to run when this transform's position has changed.
	/// </summary>
	/// <param name="callback">A function which takes a Vector3 parameter as reference (Vector3<T>& position).</param>
	void SetOnPositionChangedFunc(void (*callback)(Vector3<T>));

	/// <summary>
	/// Assign the function to run when this transform's rotation has changed.
	/// </summary>
	/// <param name="callback">A function which takes a Vector3 parameter as reference (Vector3<T>& rotation).</param>
	void SetOnRotationChangedFunc(void (*callback)(Vector3<T>));

	/// <summary>
	/// Assign the function to run when this transform's scale has changed.
	/// </summary>
	/// <param name="callback">A function which takes a Vector3 parameter as reference (Vector3<T>& scale).</param>
	void SetOnScaleChangedFunc(void (*callback)(Vector3<T>));

protected:

	Vector3<T> position;
	Vector3<T> rotation;
	Vector3<T> scale;

	Transform* parent;
	int child_index;

	int child_count;
	//Transform** children;
	std::vector<Transform*> children;
	void (*anyChangedFunc)(Vector3<T>, Vector3<T>, Vector3<T>);
	void (*posChangedFunc)(Vector3<T>);
	void (*rotChangedFunc)(Vector3<T>);
	void (*scaleChangedFunc)(Vector3<T>);

	bool is_root;
	static Transform* root_transform;
};

