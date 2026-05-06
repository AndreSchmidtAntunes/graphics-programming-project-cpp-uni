#include "imguiHelper.h"

#include "Camera.h"
#include "GLExtras.h"
#include "imguiLibs.h"
#include "Scene.h"
#include "Transform.h"
#include "Vector3.h"
#include <string>

namespace ImGuiHelper {

	const static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoFocusOnAppearing;
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

		for (auto child : scene->root->getChildren()) {
			DrawImGuiTransformFamily(io, child, &camera_following_radio_value);
		}

		ImGui::End();
	}

	void DrawImGuiTransformFamily(ImGuiIO& io, Basic_Transform* transform, int* camera_following_radio_value) {
		std::string name = "transform " + std::to_string(transform->getChildIndex());
		const char* heading = name.c_str();

		ImVec2 offset = ImGui::GetWindowPos();
		offset.y += 20;
		offset.x += 50;

		if (ImGui::CollapsingHeader(transform->getName()))
		{
			ImGui::BeginChild(heading, ImVec2(-1, 0), auto_resize_child_flags | ImGuiChildFlags_Borders);
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
					ImGuiHelper::DrawImGuiVector3(transform->local_position,	"\nPosition");
					ImGuiHelper::DrawImGuiVector3(transform->local_scale,		"\n   Scale");
					ImGui::Text("\nRotation"); ImGui::SameLine(0);
					ImGuiHelper::DrawImGuiQuaternion(transform->local_rotation, "Rotation");
				}

				if (transform->childCount() > 0)
					if (ImGui::CollapsingHeader("children", ImGuiTreeNodeFlags_Bullet)) {

						for (auto child : transform->getChildren()) {
							ImGui::Text("     ");
							ImGui::SameLine(0);
							ImGui::BeginGroup();

							ImGuiHelper::DrawImGuiTransformFamily(io, child, &ImGuiHelper::camera_following_radio_value);
							ImGui::EndGroup();
						}
					}
				transform->DrawImGuiData(io);
			}
			ImGui::EndChild();
		}
	}

	void DrawImGuiInlineFloat3(float* values, const char* x_label, const char* y_label, const char* z_label) {

		const float float_input_width = 100.0f;

		ImGui::PushItemWidth(float_input_width);
		
		//ImGui::SameLine(0);	
		ImGui::BeginGroup();
			ImGui::InputFloat(x_label, &values[0], 0.1f, 1.0f, "%.1f");
			ImGui::SameLine(0); 
			ImGui::BeginGroup();
				ImGui::InputFloat(y_label, &values[1], 0.1f, 1.0f, "%.1f");
				ImGui::SameLine(0); 
				ImGui::BeginGroup();
					ImGui::InputFloat(z_label, &values[2], 0.1f, 1.0f, "%.1f");
				ImGui::EndGroup();
			ImGui::EndGroup();
		ImGui::EndGroup();

		ImGui::PopItemWidth();
	}

	void DrawImGuiVector3(Vector3& vector3, const char* label, const char* x_label, const char* y_label, const char* z_label) {
		ImGui::Text(label); ImGui::SameLine(0);
		ImGui::BeginChild(label, ImVec2(-1, 0), auto_resize_child_flags | ImGuiChildFlags_Borders);
			DrawImGuiInlineFloat3(&vector3[0], x_label, y_label, z_label);
		ImGui::EndChild();
	}

	void DrawImGuiQuaternion(Quaternion& quat, const char* str_id, const char* w_label,  const char* x_label, const char* y_label, const char* z_label) {
		ImGui::BeginChild(str_id, ImVec2(-1, 0), auto_resize_child_flags | ImGuiChildFlags_Borders);
			DrawImGuiInlineFloat3(&(quat.x), x_label, y_label, z_label);
			ImGui::SliderFloat(" ", &(quat.w), -1, 1);
			ImGui::SameLine(0); ImGui::Text(w_label);
		ImGui::EndChild();
	}
} // namespace ImGuiHelper