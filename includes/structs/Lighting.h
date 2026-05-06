#pragma once

#include "Basic_Transform.h"
#include "Colour.h"
#include "Vector3.h"
#include <bitset>

#define SAFE_MINIMUM_LIGHT_COUNT 8

enum Light_Type : int {
	Direction = 0,  // the light is positioned at infinity
	Position = 1
};

class Light : public Basic_Transform {

	using Basic_Transform::Basic_Transform;

	size_t _light_index;

	bool _dirty_light = true; // A dirty light means that it was made with no available light slots.

	static std::bitset<SAFE_MINIMUM_LIGHT_COUNT> _taken_IDs; // stores which ids are available to instantiate a light with.

	static void setLight(const Light* const light);

public:

	int light_type = Light_Type::Position; // placed at a position in space within the scene

	void Draw() const {
		setLight(this);
	}

	void DrawImGuiData(ImGuiIO& io);

	Colour ambient;
	Colour diffuse;
	Colour specular;

	Light(const char* name, Basic_Transform* const parent, const Vector3& local_position = Vector3::Zero, const Colour& ambient = Colour(0.5, 0.5, 0.5, 1), const Colour& diffuse = Colour(0.5, 0.5, 0.5, 1), const Colour& specular = Colour(0.5, 0.5, 0.5, 1));
};

inline std::bitset<SAFE_MINIMUM_LIGHT_COUNT> Light::_taken_IDs = 0;

#undef SAFE_MINIMUM_LIGHT_COUNT