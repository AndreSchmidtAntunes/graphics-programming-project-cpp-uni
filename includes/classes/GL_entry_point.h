#pragma once

class Camera;
struct ImGuiIO;
class Scene;

class GL_entry_point {
public:

	float deltaTime;
	float rot;

	GL_entry_point(int argc, char* argv[]);
	~GL_entry_point(void);

	void Update();
	void Render();

	Camera* camera;
};
