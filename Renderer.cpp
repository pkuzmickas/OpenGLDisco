#include "Renderer.h"
using namespace glm;
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
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
}

void Renderer::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);

	for (auto obj : drawQueue) {
		glBindBuffer(GL_ARRAY_BUFFER, obj.posBufferId);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, obj.colorBufferId);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, obj.normalBufferId);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		mat4 model = mat4(1.0f);
		model = translate(model, vec3(0.5f, 0, 0));
		model = rotate(model, 45.0f, vec3(1, 1, 0));
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);


		glDrawArrays(GL_TRIANGLES, 0, obj.numberOfVertices);

		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glUseProgram(0);
}

void Renderer::createObject(Renderer::Objects objectType) {

	GLfloat* pos = NULL;
	GLfloat* color = NULL;
	GLfloat* normals = NULL;
	int sizeP, sizeC, sizeN;
	Object obj;
	switch (objectType) {
	case CUBE: {
		Cube::createCube(pos, color, normals, sizeP, sizeC, sizeN);
		obj.numberOfVertices = 36;
		break;
	}
	default: {
		Cube::createCube(pos, color, normals, sizeP, sizeC, sizeN);
		obj.numberOfVertices = sizeP / 3;
		break;
	}
	}
	//Object obj;
	//obj.numberOfVertices = 36;
	//GLfloat pos[] =
	//{
	//	-0.25f, 0.25f, -0.25f,
	//	-0.25f, -0.25f, -0.25f,
	//	0.25f, -0.25f, -0.25f,

	//	0.25f, -0.25f, -0.25f,
	//	0.25f, 0.25f, -0.25f,
	//	-0.25f, 0.25f, -0.25f,

	//	0.25f, -0.25f, -0.25f,
	//	0.25f, -0.25f, 0.25f,
	//	0.25f, 0.25f, -0.25f,

	//	0.25f, -0.25f, 0.25f,
	//	0.25f, 0.25f, 0.25f,
	//	0.25f, 0.25f, -0.25f,

	//	0.25f, -0.25f, 0.25f,
	//	-0.25f, -0.25f, 0.25f,
	//	0.25f, 0.25f, 0.25f,

	//	-0.25f, -0.25f, 0.25f,
	//	-0.25f, 0.25f, 0.25f,
	//	0.25f, 0.25f, 0.25f,

	//	-0.25f, -0.25f, 0.25f,
	//	-0.25f, -0.25f, -0.25f,
	//	-0.25f, 0.25f, 0.25f,

	//	-0.25f, -0.25f, -0.25f,
	//	-0.25f, 0.25f, -0.25f,
	//	-0.25f, 0.25f, 0.25f,

	//	-0.25f, -0.25f, 0.25f,
	//	0.25f, -0.25f, 0.25f,
	//	0.25f, -0.25f, -0.25f,

	//	0.25f, -0.25f, -0.25f,
	//	-0.25f, -0.25f, -0.25f,
	//	-0.25f, -0.25f, 0.25f,

	//	-0.25f, 0.25f, -0.25f,
	//	0.25f, 0.25f, -0.25f,
	//	0.25f, 0.25f, 0.25f,

	//	0.25f, 0.25f, 0.25f,
	//	-0.25f, 0.25f, 0.25f,
	//	-0.25f, 0.25f, -0.25f,
	//};

	///* Manually specified colours for our cube */
	//GLfloat color[] = {
	//	0.0f, 0.0f, 1.0f, 1.0f,
	//	0.0f, 0.0f, 1.0f, 1.0f,
	//	0.0f, 0.0f, 1.0f, 1.0f,
	//	0.0f, 0.0f, 1.0f, 1.0f,
	//	0.0f, 0.0f, 1.0f, 1.0f,
	//	0.0f, 0.0f, 1.0f, 1.0f,

	//	0.0f, 1.0f, 0.0f, 1.0f,
	//	0.0f, 1.0f, 0.0f, 1.0f,
	//	0.0f, 1.0f, 0.0f, 1.0f,
	//	0.0f, 1.0f, 0.0f, 1.0f,
	//	0.0f, 1.0f, 0.0f, 1.0f,
	//	0.0f, 1.0f, 0.0f, 1.0f,

	//	1.0f, 1.0f, 0.0f, 1.0f,
	//	1.0f, 1.0f, 0.0f, 1.0f,
	//	1.0f, 1.0f, 0.0f, 1.0f,
	//	1.0f, 1.0f, 0.0f, 1.0f,
	//	1.0f, 1.0f, 0.0f, 1.0f,
	//	1.0f, 1.0f, 0.0f, 1.0f,

	//	1.0f, 0.0f, 0.0f, 1.0f,
	//	1.0f, 0.0f, 0.0f, 1.0f,
	//	1.0f, 0.0f, 0.0f, 1.0f,
	//	1.0f, 0.0f, 0.0f, 1.0f,
	//	1.0f, 0.0f, 0.0f, 1.0f,
	//	1.0f, 0.0f, 0.0f, 1.0f,

	//	1.0f, 0.0f, 1.0f, 1.0f,
	//	1.0f, 0.0f, 1.0f, 1.0f,
	//	1.0f, 0.0f, 1.0f, 1.0f,
	//	1.0f, 0.0f, 1.0f, 1.0f,
	//	1.0f, 0.0f, 1.0f, 1.0f,
	//	1.0f, 0.0f, 1.0f, 1.0f,

	//	0.0f, 1.0f, 1.0f, 1.0f,
	//	0.0f, 1.0f, 1.0f, 1.0f,
	//	0.0f, 1.0f, 1.0f, 1.0f,
	//	0.0f, 1.0f, 1.0f, 1.0f,
	//	0.0f, 1.0f, 1.0f, 1.0f,
	//	0.0f, 1.0f, 1.0f, 1.0f,
	//};

	///* Manually specified normals for our cube */
	//GLfloat normals[] =
	//{
	//	0, 0, -1.f, 0, 0, -1.f, 0, 0, -1.f,
	//	0, 0, -1.f, 0, 0, -1.f, 0, 0, -1.f,
	//	1.f, 0, 0, 1.f, 0, 0, 1.f, 0, 0,
	//	1.f, 0, 0, 1.f, 0, 0, 1.f, 0, 0,
	//	0, 0, 1.f, 0, 0, 1.f, 0, 0, 1.f,
	//	0, 0, 1.f, 0, 0, 1.f, 0, 0, 1.f,
	//	-1.f, 0, 0, -1.f, 0, 0, -1.f, 0, 0,
	//	-1.f, 0, 0, -1.f, 0, 0, -1.f, 0, 0,
	//	0, -1.f, 0, 0, -1.f, 0, 0, -1.f, 0,
	//	0, -1.f, 0, 0, -1.f, 0, 0, -1.f, 0,
	//	0, 1.f, 0, 0, 1.f, 0, 0, 1.f, 0,
	//	0, 1.f, 0, 0, 1.f, 0, 0, 1.f, 0,
	//};

	/* Create the vertex buffer for the cube */
	glGenBuffers(1, &obj.posBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, obj.posBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36 * 3, pos, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Create the colours buffer for the cube */
	glGenBuffers(1, &obj.colorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, obj.colorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36* 4, color, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Create the normals  buffer for the cube */
	glGenBuffers(1, &obj.normalBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, obj.normalBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36*3, normals, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	drawQueue.push_back(obj);
}
