#pragma once
#include <GLFW/glfw3.h>
#include <vector>
class Cube {
	Cube() {};
public:
	static void createCube(int rgb[3], GLfloat*& pos, GLfloat*& color, GLfloat*& normals, GLint& sizeP, GLint& sizeC, GLint& sizeN);
};