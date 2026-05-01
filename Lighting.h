#pragma once

#include "Colour.h"
#include "Vector4.h"
#include "GLLibs.h"

struct Light {

	Colour ambient;
	Colour diffuse;
	Colour specular;

	Vector4 position;

	Light(const Colour& ambient = Colour(0.65, 0.65, 0.65, 1), const Colour& diffuse = Colour(0.75, 0.75, 0.75, 1), const Colour& specular = Colour(0.5, 0.5, 0.5, 1)) : ambient(ambient), diffuse(diffuse), specular(specular) {}

	void init() {
		setLight(this);
	}

	static void setLight(Light *light) {
		glLightfv(GL_LIGHT0, GL_AMBIENT, &light->ambient[0]);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, &light->diffuse[0]);
		glLightfv(GL_LIGHT0, GL_SPECULAR, &light->specular[0]);
		glLightfv(GL_LIGHT0, GL_POSITION, &light->position[0]);
	}
};