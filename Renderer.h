#pragma once
#include <vector>
#define GLEW_STATIC

#pragma comment(lib, "glfw3D.lib")
#pragma comment(lib, "glew32sd.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "soil.lib")

#include <SOIL.h>
#include "Camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Cube.h"
#include "ShaderHandler.h"
#include "Globals.h"
#include "sphere.h"

using namespace std;
class Shader;
class Renderer {
public:
	enum Objects {
		CUBE,
		SKYBOX
	};
	struct Object {
		GLuint posBufferId;
		GLuint colorBufferId;
		GLuint normalBufferId;
		GLuint textureBufferId = -1;
		GLsizei numberOfVertices;
		glm::mat4* model = NULL;
	};
	Renderer();
	~Renderer();
	void draw();
	// Creates an object and returns a reference to its model
	glm::mat4* createObject(Renderer::Objects objectType, int rgb[3]);

	mat4* skybox;

	static float aspectRatio;
	static bool drawDisco;
	Sphere discoBall;

private:
	vector<Object> drawQueue;
	GLuint program;
	GLuint textureProgram;
	GLuint skyboxTexture;
	ShaderHandler shaderHandler;
	GLint modelID, viewID, projectionID, lightID;
	GLint textureModelID, textureViewID, textureProjectionID, textureID;

};