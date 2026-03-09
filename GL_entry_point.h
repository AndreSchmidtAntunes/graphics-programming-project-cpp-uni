#pragma once

class GL_entry_point {
public:
	float rot;

	void Display();

	void DrawPolygons();

	void Update();

	GL_entry_point(int argc, char* argv[]);

	~GL_entry_point(void);


};
