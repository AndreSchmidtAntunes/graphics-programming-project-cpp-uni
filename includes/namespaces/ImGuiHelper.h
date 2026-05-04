#pragma once

#include "Vector3.h"
#include "Colour.h"
#include "Quaternion.h"

struct ImGuiIO;
class Transform;
class Scene;

namespace ImGuiHelper {

static bool show_fps = true;
static bool show_scene_hierarchy = true;

static int camera_following_radio_value = 0;

void FPS(ImGuiIO& io, float delta_time);

void DrawImGuiVector3(Vector3& vector3, const char* label, const char* x_label = "x", const char* y_label = "y", const char* z_label = "z");
void DrawImGuiQuaternion(Quaternion& quat, const char* label, const char* w_label = "w", const char* x_label = "x", const char* y_label = "y", const char* z_label = "z");

void SceneTree(ImGuiIO& io, Scene* const scene, Colour* bg_colour = nullptr);

void DrawImGuiTransformFamily(Transform* const transform, int* camera_following_radio_value, int* camera_following_radio_index);

} // namespace ImGuiHelper