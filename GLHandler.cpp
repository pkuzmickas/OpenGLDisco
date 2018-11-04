#include "GLHandler.h"
#include <stdlib.h> 
#include <time.h> 
using namespace std;

bool GLHandler::sceneInit = false;

GLHandler::GLHandler() {
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW." << endl;
		exit(EXIT_FAILURE);
	}
	window = glfwCreateWindow(Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT, APP_TITLE, NULL, NULL);
	if (!window) {
		std::cout << "Could not open GLFW window." << endl;
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

	srand(time(NULL));	

	float startPos = -10.f;
	for (int i = 0; i < 20; i++) {
		int rgb[2][3] = { { rand() % 255 , rand() % 255, rand() % 255 }, { rand() % 255 , rand() % 255 , rand() % 255 } };
		characters.push_back(new Character(renderer, vec3(0, 0, startPos + i*1.6f), rgb));
	}
	

	std::cout << "-------------------------------------" << endl;
	std::cout << "WELCOME TO THE DISCO" << endl;
	std::cout << "-------------------------------------" << endl;
	std::cout << "Press ENTER to UNLEASH the disco!" << endl;
	

}

GLHandler::~GLHandler() {
	if (renderer)
		delete renderer;
	for (auto ch : characters) {
		delete ch;
	}
}

void GLHandler::errorCallback(int error, const char * desc) {
	fputs(desc, stderr);
}

void GLHandler::keyCallback(GLFWwindow * window, int key_code, int scancode, int action, int mods) {
	if (action == GLFW_PRESS)
	{
		//camera movement
		if (key_code == GLFW_KEY_W)
			Camera::move(Camera::movingDir::FORWARD, true);
		/*Camera::camera = translate(Camera::camera, vec3(-0.1f, 0, 0));*/
		else if (key_code == GLFW_KEY_S)
			Camera::move(Camera::movingDir::BACKWARD, true);

		if (key_code == GLFW_KEY_A)
			Camera::move(Camera::movingDir::LEFT, true);
		else if (key_code == GLFW_KEY_D)
			Camera::move(Camera::movingDir::RIGHT, true);
		
		if (key_code == GLFW_KEY_ENTER) {
			GLHandler::sceneInit = true;
			Renderer::drawDisco = true;
			std::cout << endl << endl << endl;
			std::cout << "*************************************" << endl;
			std::cout << "THE DISCO HAS BEGUN" << endl;
			std::cout << "*************************************" << endl;
			std::cout << "Controls:" << endl;
			std::cout << "W - Zoom In" << endl;
			std::cout << "S - Zoom Out" << endl;
			std::cout << "A - Rotate Left" << endl;
			std::cout << "D - Rotate Right" << endl;
			std::cout << "F - Increase Dance Speed" << endl;
			std::cout << "G - Decrease Dance Speed" << endl;
		}
		if (key_code == GLFW_KEY_F) {
			if (Character::danceSpeed <= 500) {
				Character::danceSpeed += 50;
			}
			
		}
		if (key_code == GLFW_KEY_G) {
			if (Character::danceSpeed >= 100) {
				Character::danceSpeed -= 50;
			}
		}
		// CHANGE CLOTHES?
	}
	if (action == GLFW_RELEASE)
	{
		//camera movement
		if (key_code == GLFW_KEY_W)
			Camera::move(Camera::movingDir::FORWARD, false);
		/*Camera::camera = translate(Camera::camera, vec3(-0.1f, 0, 0));*/
		else if (key_code == GLFW_KEY_S)
			Camera::move(Camera::movingDir::BACKWARD, false);

		if (key_code == GLFW_KEY_A)
			Camera::move(Camera::movingDir::LEFT, false);
		else if (key_code == GLFW_KEY_D)
			Camera::move(Camera::movingDir::RIGHT, false);
		
	}
}

void GLHandler::reshapeCallback(GLFWwindow * window, int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	Renderer::aspectRatio = float(width) / float(height);
}

void GLHandler::play() {
	while (!glfwWindowShouldClose(window))
	{
		update();
		renderer->draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void GLHandler::update() {
	deltaTime = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();

	Camera::update(deltaTime);

	for (auto c : characters) {
		c->update(deltaTime);
	}

	if (GLHandler::sceneInit && !initialized) {
		initialized = true;
		Camera::camera = lookAt(
			vec3(-13, 8, 2),
			vec3(3, 0, -2),
			vec3(0, 1, 0)
		);
		/*characters[0]->move(vec3(8, 0, 1.5f));
		characters[2]->move(vec3(0, 0, 0.5f));
		characters[3]->move(vec3(8, 0, -0.5f));
		characters[0]->dance(0);
		characters[1]->dance(0);
		characters[2]->dance(0);
		characters[3]->dance(0);*/
		for (int i = 0; i < characters.size(); i++) {
			if (i < characters.size() / 4) {
				characters[i]->move(vec3(8, 0, 7 ));
			}
			else if (i >= characters.size() / 4 * 2 && i < characters.size() / 4 * 3) {
				characters[i]->move(vec3(16, 0, -15));
			}
			else if (i >= characters.size() / 4 * 3) {
				characters[i]->move(vec3(22, 0, -24));
			}
			else {
				characters[i]->move(vec3(0, 0, -5));
			}
			characters[i]->dance(0);

		}
	}
}
