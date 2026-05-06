#include "Lighting.h"

#include "GLLibs.h"
#include "imguiLibs.h"
#include <iostream>

void Light::setLight(const Light* const light) {

	if (light->_dirty_light) {
		throw std::out_of_range("Cannot draw light" + std::string(light->_name) + "as the number of lights has been maxed out.");
	}

	glLightfv(GL_LIGHT0 + light->_light_index, GL_AMBIENT, &(light->ambient[0]));
	glLightfv(GL_LIGHT0 + light->_light_index, GL_DIFFUSE, &(light->diffuse[0]));
	glLightfv(GL_LIGHT0 + light->_light_index, GL_SPECULAR, &(light->specular[0]));
	glLightfv(GL_LIGHT0 + light->_light_index, GL_POSITION, &((light->getWorldPosition() + (Vector4::Ana * light->light_type))[0]));
}

Light::Light(const char* name, Basic_Transform* const parent, const Vector3& local_position, const Colour& ambient, const Colour& diffuse, const Colour& specular)
	: ambient(ambient), diffuse(diffuse), specular(specular), Basic_Transform(name, parent, local_position) {
	for (int i = 0; i < _taken_IDs.size(); i++)
		if (_taken_IDs[i] == false) {
			_taken_IDs.set(i, true);
			_light_index = i;
			_dirty_light = false;

			glEnable(GL_LIGHT0 + _light_index);

			return;
		}
	throw std::out_of_range("All GL Light slots have been filled. Light Object with name \"" + std::string(name) + "\" Failed instantiation.");
}

static const ImGuiColorEditFlags colourEditImGuiFlags = ImGuiColorEditFlags_DisplayHex | ImGuiColorEditFlags_AlphaBar;
const static ImGuiChildFlags auto_resize_child_flags = ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY;

void Light::DrawImGuiData(ImGuiIO& io) {
	if (ImGui::CollapsingHeader("Emission", ImGuiTreeNodeFlags_Bullet)) {

		static const char* type_list[] = { "Direction", "Position" };

		ImGui::Combo("MyCombo", &light_type, type_list, IM_ARRAYSIZE(type_list));
		
		ImGui::BeginChild("Light Colour Values", ImVec2(-1,0), auto_resize_child_flags | ImGuiChildFlags_Borders);
			ImGui::ColorEdit4(" Ambiant",  &(ambient[0]), colourEditImGuiFlags);
			ImGui::ColorEdit4(" Diffuse",  &(diffuse[0]), colourEditImGuiFlags);
			ImGui::ColorEdit4("Specular", &(specular[0]), colourEditImGuiFlags);
		ImGui::EndChild();
	}
}