#pragma once

class Camera;

class GL_entry_point {
public:

	float deltaTime;
	float rot;

	GL_entry_point(int argc, char* argv[]);
	~GL_entry_point(void);

	void Update();

	void Display();
	void DrawPolygons();

//private:
	Camera* camera;
};
