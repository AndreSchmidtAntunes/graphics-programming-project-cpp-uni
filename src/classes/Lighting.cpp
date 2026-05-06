#include "Lighting.h"

#include "GLLibs.h"
#include <iostream>

void Light::setLight(const Light* const light) {

	if (light->_dirty_light) {
		throw std::out_of_range("Cannot draw light" + std::string(light->_name) + "as the number of lights has been maxed out.");
	}

	glLightfv(GL_LIGHT0 + light->_light_index, GL_AMBIENT, &(light->ambient[0]));
	glLightfv(GL_LIGHT0 + light->_light_index, GL_DIFFUSE, &(light->diffuse[0]));
	glLightfv(GL_LIGHT0 + light->_light_index, GL_SPECULAR, &(light->specular[0]));
	glLightfv(GL_LIGHT0 + light->_light_index, GL_POSITION, &(light->getWorldPosition()[0]));
}

Light::Light(const char* name, Basic_Transform* const parent, const Vector3& local_position, const Colour& ambient, const Colour& diffuse, const Colour& specular)
	: ambient(ambient), diffuse(diffuse), specular(specular), Basic_Transform(name, parent, local_position) {
	for (int i = 0; i < _taken_IDs.size(); i++)
		if (_taken_IDs[i] == false) {
			_taken_IDs.set(i, true);
			_light_index = i;
			_dirty_light = false;
			return;
		}
	throw std::out_of_range("All GL Light slots have been filled. Light Object with name \"" + std::string(name) + "\" Failed instantiation.");
}