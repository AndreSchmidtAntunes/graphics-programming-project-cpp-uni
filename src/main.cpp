#include "GL_entry_point.h"

#include <iostream>

#include "Vector.h"
//#include "Vector2.h"
#include "Vector3.h"
//#include "Vector4.h"
//#include "Matrix3x3.h"
//#include "Matrix4x4.h"

int main(int argc, char* argv[]) {

	Vector3<float> test(4, 1, 5);
	Vectors::Vector<short, 7> test2 = Vectors::Zero;
	std::cout << Vectors::Right + test;

	GL_entry_point* game = new GL_entry_point(argc, argv);


	

	return 0;

	
}