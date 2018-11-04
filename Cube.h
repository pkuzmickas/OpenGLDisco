/* Cube.h
 Static class to control the creation of a cube.
 Paulius Kuzmickas October 2018.
*/
#pragma once
#include <GLFW/glfw3.h>
#include <vector>
class Cube {
	Cube() {};
public:
	static void createCube(int rgb[3], GLfloat*& pos, GLfloat*& color, GLfloat*& normals, GLint& sizeP, GLint& sizeC, GLint& sizeN, bool isSkybox = false);
	static void createTexture(GLfloat*& texture, GLint& sizeT);
};