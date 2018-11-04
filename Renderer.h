#pragma once
#include <vector>
#define GLEW_STATIC

#pragma comment(lib, "glfw3D.lib")
#pragma comment(lib, "glew32sd.lib")
#pragma comment(lib, "opengl32.lib")

#include "Camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Cube.h"
#include "ShaderHandler.h"
#include "Globals.h"


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
		glm::mat4* model = NULL;
	};
	Renderer();
	~Renderer();
	void draw();
	// Creates an object and returns a reference to its model
	glm::mat4* createObject(Renderer::Objects objectType, int rgb[3]);
	static float aspectRatio;

private:
	vector<Object> drawQueue;
	GLuint program;
	ShaderHandler shaderHandler;
	GLint modelID, viewID, projectionID;
	

};