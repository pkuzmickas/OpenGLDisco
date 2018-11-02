#include "Renderer.h"
using namespace glm;
mat4 Renderer::Camera;
Renderer::Renderer() {
	try
	{
		program = shaderHandler.loadShader("shader.vert", "shader.frag");
	}
	catch (exception &e)
	{
		cout << "Caught exception: " << e.what() << endl;
		cin.ignore();
		exit(0);
	}
	modelID = glGetUniformLocation(program, "model");
	viewID = glGetUniformLocation(program, "view");
	projectionID = glGetUniformLocation(program, "projection");

	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);

	Camera = glm::lookAt(
		glm::vec3(-5, 0, 0),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
}

Renderer::~Renderer() {
	for (auto drw : drawQueue) {
		if (drw.model) {
			delete drw.model;
		}
	}
}

void Renderer::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(program);
	
	for (auto obj : drawQueue) {
		glBindBuffer(GL_ARRAY_BUFFER, obj.posBufferId);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, Globals::NUM_OF_VALUES_POSITION, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, obj.colorBufferId);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, Globals::NUM_OF_VALUES_COLOR, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, obj.normalBufferId);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, Globals::NUM_OF_VALUES_NORMAL, GL_FLOAT, GL_FALSE, 0, 0);

		mat4 model = *obj.model;

		
		mat4 view = Camera;
		view = translate(view, vec3(0.5f, 0, 0));

		glm::mat4 projection = glm::perspective(glm::radians(30.0f), (float)Globals::WINDOW_WIDTH / Globals::WINDOW_HEIGHT, 0.1f, 100.f);
		
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projection[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, obj.numberOfVertices);

		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glUseProgram(0);
}

glm::mat4* Renderer::createObject(Renderer::Objects objectType, int rgb[3]) {

	GLfloat* pos = NULL;
	GLfloat* color = NULL;
	GLfloat* normals = NULL;
	int sizeP, sizeC, sizeN;
	Object obj;
	switch (objectType) {
	case CUBE: {
		Cube::createCube(rgb, pos, color, normals, sizeP, sizeC, sizeN);
		obj.numberOfVertices = sizeP / Globals::NUM_OF_VALUES_POSITION;
		break;
	}
	default: {
		Cube::createCube(rgb, pos, color, normals, sizeP, sizeC, sizeN);
		obj.numberOfVertices = sizeP / Globals::NUM_OF_VALUES_POSITION;
		break;
	}
	}

	/* Create the vertex buffer for the cube */
	glGenBuffers(1, &obj.posBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, obj.posBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * obj.numberOfVertices * Globals::NUM_OF_VALUES_POSITION, pos, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Create the colours buffer for the cube */
	glGenBuffers(1, &obj.colorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, obj.colorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * obj.numberOfVertices* Globals::NUM_OF_VALUES_COLOR, color, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Create the normals  buffer for the cube */
	glGenBuffers(1, &obj.normalBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, obj.normalBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * obj.numberOfVertices* Globals::NUM_OF_VALUES_NORMAL, normals, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	obj.model = new mat4(1.0f);
	
	drawQueue.push_back(obj);
	
	return obj.model;
}
