#pragma once

#include "Colour.h"
#include "GLLibs.h"

struct Material {

	Colour ambient;
	Colour diffuse;
	Colour specular;

	float shininess;

	Material(const Colour& ambient = Colour(0.65, 0.65, 0.65, 1), const Colour& diffuse = Colour(0.75, 0.75, 0.75, 1), const Colour& specular = Colour(0.5, 0.5, 0.5, 1), const float shininess = 0.25) : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

	static void setMatrial(Material* mat) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, &mat->ambient[0]);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat->diffuse[0]);
		glMaterialfv(GL_FRONT, GL_SPECULAR, &mat->specular[0]);
		glMaterialf(GL_FRONT, GL_SHININESS, mat->shininess);
	}
};