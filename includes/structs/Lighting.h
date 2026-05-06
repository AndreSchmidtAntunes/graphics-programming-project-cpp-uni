#pragma once

#include "Basic_Transform.h"

#include "Colour.h"
#include "Vector3.h"
#include <bitset>

#define SAFE_MINIMUM_LIGHT_COUNT 8

class Light : public Basic_Transform { /// TODO: get this displaying in editor and allow changing of values

	using Basic_Transform::Basic_Transform;

	size_t _light_index;

	bool _dirty_light = true; // A dirty light means that it was made with no available light slots.

	static std::bitset<SAFE_MINIMUM_LIGHT_COUNT> _taken_IDs; // stores which ids are available to instantiate a light with.

	static void setLight(const Light* const light);

public:

	void Draw() const {
		setLight(this);
	}

	Colour ambient;
	Colour diffuse;
	Colour specular;

	Light(const char* name, Basic_Transform* const parent, const Vector3& local_position, const Colour& ambient = Colour(0.65, 0.65, 0.65, 1), const Colour& diffuse = Colour(0.75, 0.75, 0.75, 1), const Colour& specular = Colour(0.5, 0.5, 0.5, 1));
};