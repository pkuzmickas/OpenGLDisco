/* GLHandler.h
 Class to control the OpenGL functions, callbacks and creating and controlling the window.
 Has the draw loop with updates.
 One of the main classes of the program.
 Paulius Kuzmickas October 2018.
*/
#pragma once

#include "Globals.h"

#include "Character.h"
#include <iostream>
#include "sphere.h"

class GLHandler {
private:
	GLFWwindow* window;
	Renderer* renderer = NULL;
	float deltaTime, lastTime = 0;
	vector<Character*> characters;
	bool initialized = false;
public:
	GLHandler();
	~GLHandler();
	static void errorCallback(int error, const char* desc);
	static void keyCallback(GLFWwindow* window, int key_code, int scancode, int action, int mods);
	static void reshapeCallback(GLFWwindow* window, int width, int height);
	static bool sceneInit;
	void play();
	void update();
};