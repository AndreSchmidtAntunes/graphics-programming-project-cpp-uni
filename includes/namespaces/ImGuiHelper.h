#pragma once

#include "imguiLibs.h"
#include "Colour.h"
#include "Quaternion.h"
#include "Vector3.h"

struct ImGuiIO;
class Basic_Transform;
class Scene;

namespace ImGuiHelper {

static bool show_fps = true;
static bool show_scene_hierarchy = true;

static int camera_following_radio_value = 0;

void FPS(ImGuiIO& io, float delta_time);

void DrawImGuiVector3(Vector3& vector3, const char* label, const char* x_label = "x", const char* y_label = "y", const char* z_label = "z");
void DrawImGuiQuaternion(Quaternion& quat, const char* label, const char* w_label = "Imaginary", const char* x_label = "x", const char* y_label = "y", const char* z_label = "z");

void SceneTree(ImGuiIO& io, Scene* const scene, Colour* bg_colour = nullptr);

void DrawImGuiTransformFamily(ImGuiIO& io, Basic_Transform* transform, int* camera_following_radio_value);

} // namespace ImGuiHelper