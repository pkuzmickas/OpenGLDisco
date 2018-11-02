#include "GLHandler.h"
using namespace std;

GLHandler::GLHandler() {
	if (!glfwInit())
	{
		cout << "Failed to initialize GLFW." << endl;
		exit(EXIT_FAILURE);
	}
	window = glfwCreateWindow(Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT, APP_TITLE, NULL, NULL);
	if (!window) {
		cout << "Could not open GLFW window." << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	GLenum error = glewInit();
	if (GLEW_OK != error)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	glfwSetErrorCallback(errorCallback);
	glfwSetFramebufferSizeCallback(window, reshapeCallback);
	glfwSetKeyCallback(window, keyCallback);
	
	renderer = new Renderer();
	Character::createCharacter(renderer, vec3(0, 0, 0));
}

GLHandler::~GLHandler() {
	if(renderer)
	delete renderer;
}

void GLHandler::errorCallback(int error, const char * desc) {
	fputs(desc, stderr);
}

void GLHandler::keyCallback(GLFWwindow * window, int key_code, int scancode, int action, int mods) {
	if (action == GLFW_PRESS)
	{
		//camera movement
		if (key_code == GLFW_KEY_W)
			Renderer::Camera = translate(Renderer::Camera, vec3(-0.1f, 0, 0));
		else if (key_code == GLFW_KEY_S)
			Renderer::Camera = translate(Renderer::Camera, vec3(0.1f, 0, 0));

		if (key_code == GLFW_KEY_A)
			Renderer::Camera = translate(Renderer::Camera, vec3(0, 0, 0.1f));
		else if (key_code == GLFW_KEY_D)
			Renderer::Camera = translate(Renderer::Camera, vec3(0, 0, -0.1f));
		if (key_code == GLFW_KEY_LEFT)
			Renderer::Camera = rotate(Renderer::Camera, radians(15.f), vec3(0, 0.1f, 0));
		else if (key_code == GLFW_KEY_RIGHT)
			Renderer::Camera = rotate(Renderer::Camera, radians(-15.f), vec3(0, 0.1f, 0));
		if (key_code == GLFW_KEY_UP)
			Renderer::Camera = rotate(Renderer::Camera, radians(15.f), vec3(0, 0, 0.1f));
		else if (key_code == GLFW_KEY_DOWN)
			Renderer::Camera = rotate(Renderer::Camera, radians(-15.f), vec3(0, 0, 0.1f));
	}
}

void GLHandler::reshapeCallback(GLFWwindow * window, int width, int height) {
	cout << "BYE" << endl;
}

void GLHandler::play() {
	while (!glfwWindowShouldClose(window))
	{
		//update();
		renderer->draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
