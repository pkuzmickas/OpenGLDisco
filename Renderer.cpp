#include "Renderer.h"

using namespace glm;

float Renderer::aspectRatio = (float)Globals::WINDOW_WIDTH / Globals::WINDOW_HEIGHT;
bool Renderer::drawDisco = false;
Renderer::Renderer() {
	try
	{
		program = shaderHandler.loadShader("shader.vert", "shader.frag");
		textureProgram = shaderHandler.loadShader("skybox.vert", "skybox.frag");
	}
	catch (exception &e)
	{
		cout << "Caught exception: " << e.what() << endl;
		cin.ignore();
		exit(0);
	}
	try
	{
		skyboxTexture = SOIL_load_OGL_texture("skybox.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	}
	catch (std::exception &e)
	{
		std::cerr << "Couldn't load a texture." << std::endl;
	}


	modelID = glGetUniformLocation(program, "model");
	viewID = glGetUniformLocation(program, "view");
	projectionID = glGetUniformLocation(program, "projection");
	lightID = glGetUniformLocation(program, "light");

	textureModelID = glGetUniformLocation(textureProgram, "model");
	textureViewID = glGetUniformLocation(textureProgram, "view");
	textureProjectionID = glGetUniformLocation(textureProgram, "projection");

	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);

	discoBall.makeSphere(20, 20);

	int rgb[3] = { 0,0,0 };
	skybox = createObject(SKYBOX, rgb);
	*skybox = translate(*skybox, vec3(0, 0, 0));
	*skybox = scale(*skybox, vec3(25, 12, 25));
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

	vec3 lightPos = vec3(2.5f, 2, -2);

	for (auto obj : drawQueue) {
		if (obj.textureBufferId != -1) {
			glUseProgram(textureProgram);
		}

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

		mat4 view = Camera::camera;
		view = translate(view, vec3(0.5f, 0, 0));

		mat4 projection = perspective(glm::radians(30.0f), aspectRatio, 0.1f, 200.f);

		if (obj.textureBufferId != -1) {

			glBindBuffer(GL_ARRAY_BUFFER, obj.textureBufferId);
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, Globals::NUM_OF_VALUES_TEXTURE, GL_FLOAT, GL_FALSE, 0, 0);

			glUniformMatrix4fv(textureModelID, 1, GL_FALSE, &model[0][0]);
			glUniformMatrix4fv(textureViewID, 1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(textureProjectionID, 1, GL_FALSE, &projection[0][0]);

			glBindTexture(GL_TEXTURE_2D, skyboxTexture);

		}
		else {
			vec4 light = vec4(lightPos, 1);

			glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
			glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projection[0][0]);
			glUniform4fv(lightID, 1, &light[0]);
		}

		glDrawArrays(GL_TRIANGLES, 0, obj.numberOfVertices);

		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		if (obj.textureBufferId != -1) glUseProgram(program);
	}
	//Drawing the disco ball
	if (drawDisco)
	{
		mat4 model = mat4(1.f);
		model = translate(model, lightPos);
		model = scale(model, vec3(0.4f, 0.4f, 0.4f));

		glUniformMatrix4fv(modelID, 1, GL_FALSE, &(model[0][0]));

		discoBall.drawSphere(0);
	}
	glUseProgram(0);
}


glm::mat4* Renderer::createObject(Renderer::Objects objectType, int rgb[3]) {

	GLfloat* pos = NULL;
	GLfloat* color = NULL;
	GLfloat* normals = NULL;
	GLfloat* texture = NULL;
	int sizeP, sizeC, sizeN, sizeT;
	Object obj;
	switch (objectType) {
	case CUBE: {
		Cube::createCube(rgb, pos, color, normals, sizeP, sizeC, sizeN);
		obj.numberOfVertices = sizeP / Globals::NUM_OF_VALUES_POSITION;
		break;
	}
	case SKYBOX: {
		Cube::createCube(rgb, pos, color, normals, sizeP, sizeC, sizeN, true);
		obj.numberOfVertices = sizeP / Globals::NUM_OF_VALUES_POSITION;
		Cube::createTexture(texture, sizeT);
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

	/* Create the normals buffer for the cube */
	glGenBuffers(1, &obj.normalBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, obj.normalBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * obj.numberOfVertices* Globals::NUM_OF_VALUES_NORMAL, normals, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (objectType == SKYBOX) {
		/* Create the texture buffer for the cube */
		glGenBuffers(1, &obj.textureBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, obj.textureBufferId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * obj.numberOfVertices* Globals::NUM_OF_VALUES_TEXTURE, texture, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	obj.model = new mat4(1.0f);

	drawQueue.push_back(obj);

	return obj.model;
}
