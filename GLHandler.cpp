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
	renderer->createObject(Renderer::Objects::CUBE);
}

GLHandler::~GLHandler() {
	if(renderer)
	delete renderer;
}

void GLHandler::errorCallback(int error, const char * desc) {
	fputs(desc, stderr);
}

void GLHandler::keyCallback(GLFWwindow * window, int key_code, int scancode, int action, int mods) {
	/*glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	aspect_ratio = float(width) / float(height);
}*/
	cout << "HELLO" << endl;
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
