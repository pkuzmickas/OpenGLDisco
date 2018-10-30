#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;
class ShaderHandler {
public:
	GLuint loadShader(const char *vertex_path, const char *fragment_path);
	GLuint buildShader(GLenum eShaderType, const string &shaderText);
	string readFile(const char *filePath);
};