#pragma once

class GL_entry_point {
public:
	GL_entry_point(int argc, char* argv[]);

	~GL_entry_point(void);

	void Display();

	void DrawPolygons();
};
