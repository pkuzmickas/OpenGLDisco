#pragma once
#include <vector>
#define GLEW_STATIC

#pragma comment(lib, "glfw3D.lib")
#pragma comment(lib, "glew32sd.lib")
#pragma comment(lib, "opengl32.lib")

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Cube.h"
#include "ShaderHandler.h"

using namespace std;
class Shader;
class Renderer {
public:
	enum Objects {
		CUBE,
		SPHERE
	};
	struct Object {
		GLuint posBufferId;
		GLuint colorBufferId;
		GLuint normalBufferId;
		GLsizei numberOfVertices;
	};
	Renderer();
	void draw();
	void createObject(Renderer::Objects objectType);
private:
	vector<Object> drawQueue;
	GLuint program;
	ShaderHandler shaderHandler;
	GLint modelID;


};