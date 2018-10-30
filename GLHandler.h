#pragma once

#include "Globals.h"

#include "Renderer.h"
#include <iostream>
class GLHandler {
private:
	GLFWwindow* window;
	Renderer* renderer = NULL;
public:
	GLHandler();
	~GLHandler();
	static void errorCallback(int error, const char* desc);
	static void keyCallback(GLFWwindow* window, int key_code, int scancode, int action, int mods);
	static void reshapeCallback(GLFWwindow* window, int width, int height);

	void play();
};