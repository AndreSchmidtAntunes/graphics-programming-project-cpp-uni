#include "ImGuiHelper.h"

#include "Camera.h"
#include "GLExtras.h"
#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl2.h"
#include "Scene.h"
#include "Transform.h"
#include "Vector3.h"
#include <string>

namespace ImGuiHelper {

	const static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoCollapse;
	const static ImGuiChildFlags auto_resize_child_flags = ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY;

	void FPS(ImGuiIO& io, float delta_time) {
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
		ImGui::Begin("Frame data", &show_fps, window_flags);
		ImGui::Text("Application average %.2f ms/frame (%.1f FPS) ", delta_time, 1.0f / delta_time);
		ImGui::End();
	}

	void SceneTree(ImGuiIO& io, Scene* const scene, Colour* bg_colour) {
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowSize().x, 10), ImGuiCond_FirstUseEver);
		ImGui::Begin("Scene", &show_scene_hierarchy, window_flags);

		if (bg_colour != nullptr) {
			ImGui::ColorEdit4("Background", &(*bg_colour)[0]);
			glClearColor((*bg_colour).r, (*bg_colour).g, (*bg_colour).b, (*bg_colour).a);
		}

		int camera_following_radio_index = -1;

		for (auto child : scene->root->getChildren()) {
			DrawImGuiTransformFamily(child, &camera_following_radio_value, &camera_following_radio_index);
		}

		ImGui::End();
	}

	void DrawImGuiTransformFamily(Transform* const transform, int* camera_following_radio_value, int* camera_following_radio_index) {
		(*camera_following_radio_index)++;
		std::string name = "transform " + std::to_string(transform->getChildIndex());
		const char* heading = name.c_str();

		ImVec2 offset = ImGui::GetWindowPos();
		offset.y += 20;
		offset.x += 50;

		if (ImGui::CollapsingHeader(transform->getName()))
		{
			ImGui::BeginChild(heading, ImVec2(0, 0), auto_resize_child_flags | ImGuiChildFlags_Borders);
			{
				if (ImGui::RadioButton("Follow", camera_following_radio_value, transform->getSceneTransformID())) {
					transform->getScene()->getCamera()->focused_transform = transform;
				}

				if (*camera_following_radio_value == transform->getSceneTransformID()) {
					ImGui::SameLine(0);
					if (ImGui::Button("Deselect")) {
						transform->getScene()->getCamera()->focused_transform = nullptr;
						*camera_following_radio_value = -1;
					}
				}

				if (ImGui::CollapsingHeader("Transforms", ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_DefaultOpen))
				{
					DrawImGuiVector3(transform->local_position, "Position");
					DrawImGuiVector3(transform->local_scale, "Scale   ");
					DrawImGuiQuaternion(transform->local_rotation, "Rotation");
				}


				if (transform->childCount() > 0)
				if (ImGui::CollapsingHeader("children", ImGuiTreeNodeFlags_Bullet)) {

					for (auto child : transform->getChildren()) {
						ImGui::Text("     ");
						ImGui::SameLine(0);
						ImGui::BeginGroup();
							
							DrawImGuiTransformFamily(child, camera_following_radio_value, camera_following_radio_index);
						ImGui::EndGroup();
					}
				}
			}
			ImGui::EndChild();
		}
	}

	void DrawImGuiInlineFloat3(float* values, const char* label, const char* x_label, const char* y_label, const char* z_label) {
		ImGui::BeginChild(label, ImVec2(0, 0), auto_resize_child_flags);

		const float float_input_width = 100.0f;

		ImGui::PushItemWidth(float_input_width);

		ImGui::Text(label);	
		ImGui::SameLine(0);	ImGui::BeginGroup();
			ImGui::InputFloat(x_label, &values[0], 0.1f, 1.0f, "%.1f");
			ImGui::SameLine(0); ImGui::BeginGroup();
				ImGui::InputFloat(y_label, &values[1], 0.1f, 1.0f, "%.1f");
				ImGui::SameLine(0); ImGui::BeginGroup();
					ImGui::InputFloat(z_label, &values[2], 0.1f, 1.0f, "%.1f");
				ImGui::EndGroup();
			ImGui::EndGroup();
		ImGui::EndGroup();

		ImGui::PopItemWidth();
		ImGui::EndChild();
	}

	void DrawImGuiVector3(Vector3& vector3, const char* label, const char* x_label, const char* y_label, const char* z_label) {
		DrawImGuiInlineFloat3(&vector3[0], label, x_label, y_label, z_label);
	}

	void DrawImGuiQuaternion(Quaternion& quat, const char* label, const char* w_label,  const char* x_label, const char* y_label, const char* z_label) {

		ImGui::Text(label);ImGui::SameLine(0);	
			ImGui::BeginChild(label, ImVec2(0, 0), auto_resize_child_flags | ImGuiChildFlags_Borders);
		DrawImGuiInlineFloat3(&quat.x, "Real", x_label, y_label, z_label);
		ImGui::Text("Imaginary"); ImGui::SameLine(0);	
			ImGui::SliderFloat(w_label, &quat.w, -1, 1, "%.3f");
		ImGui::EndChild();
	}
} // namespace ImGuiHelper