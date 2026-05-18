#pragma once

#include "Transform.h"
#include "Colour.h"
#include "Vector3.h"
#include <bitset>

#define SAFE_MINIMUM_LIGHT_COUNT 8

enum Light_Type : int {
	Direction = 0,  // the light is positioned at infinity
	Position = 1
};

class Light : public Transform {

	using Transform::Transform;

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
	const char* const getIcon() {
		return "Q";
	}

	const ImVec4 getHierarchyColour();

	Colour ambient;
	Colour diffuse;
	Colour specular;
	float falloff = 0.1f;

	Light(const char* name, Transform* const parent, const Vector3& local_position = Vector3::Zero, const Colour& ambient = Colour::Black, const Colour& diffuse = Colour::Black, const Colour& specular = Colour::Black);
};

inline std::bitset<SAFE_MINIMUM_LIGHT_COUNT> Light::_taken_IDs = 0;

#undef SAFE_MINIMUM_LIGHT_COUNT