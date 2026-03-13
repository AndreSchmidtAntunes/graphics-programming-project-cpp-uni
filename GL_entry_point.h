#pragma once


class GL_entry_point {
public:

	float rot;

	GL_entry_point(int argc, char* argv[]);
	~GL_entry_point(void);

	void Update();

	void Display();
	void DrawPolygons();
};
