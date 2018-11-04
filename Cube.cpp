#include "Cube.h"

void Cube::createCube(int rgb[3], GLfloat*& pos, GLfloat*& color, GLfloat*& normals, GLint& sizeP, GLint& sizeC, GLint& sizeN, bool isSkybox) {
	GLfloat vertexPositions[] =
	{
		-0.25f, 0.25f, -0.25f,
		-0.25f, -0.25f, -0.25f,
		0.25f, -0.25f, -0.25f,

		0.25f, -0.25f, -0.25f,
		0.25f, 0.25f, -0.25f,
		-0.25f, 0.25f, -0.25f,

		0.25f, -0.25f, -0.25f,
		0.25f, -0.25f, 0.25f,
		0.25f, 0.25f, -0.25f,

		0.25f, -0.25f, 0.25f,
		0.25f, 0.25f, 0.25f,
		0.25f, 0.25f, -0.25f,

		0.25f, -0.25f, 0.25f,
		-0.25f, -0.25f, 0.25f,
		0.25f, 0.25f, 0.25f,

		-0.25f, -0.25f, 0.25f,
		-0.25f, 0.25f, 0.25f,
		0.25f, 0.25f, 0.25f,

		-0.25f, -0.25f, 0.25f,
		-0.25f, -0.25f, -0.25f,
		-0.25f, 0.25f, 0.25f,

		-0.25f, -0.25f, -0.25f,
		-0.25f, 0.25f, -0.25f,
		-0.25f, 0.25f, 0.25f,

		-0.25f, -0.25f, 0.25f,
		0.25f, -0.25f, 0.25f,
		0.25f, -0.25f, -0.25f,

		0.25f, -0.25f, -0.25f,
		-0.25f, -0.25f, -0.25f,
		-0.25f, -0.25f, 0.25f,

		-0.25f, 0.25f, -0.25f,
		0.25f, 0.25f, -0.25f,
		0.25f, 0.25f, 0.25f,

		0.25f, 0.25f, 0.25f,
		-0.25f, 0.25f, 0.25f,
		-0.25f, 0.25f, -0.25f,
	};
	GLfloat vertexPositions2[] = {
		-1.f, 1.f, -.99f,//1
		-1.f, -1.f, -.99f,//2
		1.f, -1.f, -.99f,//3

		1.f, -1.f, -.99f,//3
		1.f, 1.f, -.99f,//4
		-1.f, 1.f, -.99f,//1

		// Face 1 right
		0.99f, -1.f, -1.f,//3
		0.99f, -1.f, 1.f,//1
		0.99f, 1.f, -1.f,//4

		0.99f, -1.f, 1.f,
		0.99f, 1.f, 1.f,
		0.99f, 1.f, -1.f,

		// Face 2 front
		1.f, -1.f, 0.99f,
		-1.f, -1.f, 0.99f,
		1.f, 1.f, 0.99f,

		-1.f, -1.f, 0.99f,
		-1.f, 1.f, 0.99f,
		1.f, 1.f, 0.99f,

		// Face 3 left
		-.99f, -1.f, 1.f,
		-.99f, -1.f, -1.f,
		-.99f, 1.f, 1.f,

		-.99f, -1.f, -1.f,
		-.99f, 1.f, -1.f,
		-.99f, 1.f, 1.f,

		// Face 4 bottom
		-1.f, -1.f, 1.f,
		1.f, -1.f, 1.f,
		1.f, -1.f, -1.f,

		1.f, -1.f, -1.f,
		-1.f, -1.f, -1.f,
		-1.f, -1.f, 1.f,

		// Face 5 top
		-1.f, 1.f, -1.f,
		1.f, 1.f, -1.f,
		1.f, 1.f, 1.f,

		1.f, 1.f, 1.f,
		-1.f, 1.f, 1.f,
		-1.f, 1.f, -1.f,
	};


	float r = (float)rgb[0] / 255;
	float g = (float)rgb[1] / 255;
	float b = (float)rgb[2] / 255;

	/* Manually specified colours for our cube */
	GLfloat vertexColours[] = {

		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,

		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,

		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,

		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,

		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,

		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
	};

	/* Manually specified normals for our cube */
	GLfloat nrmls[] =
	{
		0, 0, -1.f, 0, 0, -1.f, 0, 0, -1.f,
		0, 0, -1.f, 0, 0, -1.f, 0, 0, -1.f,
		1.f, 0, 0, 1.f, 0, 0, 1.f, 0, 0,
		1.f, 0, 0, 1.f, 0, 0, 1.f, 0, 0,
		0, 0, 1.f, 0, 0, 1.f, 0, 0, 1.f,
		0, 0, 1.f, 0, 0, 1.f, 0, 0, 1.f,
		-1.f, 0, 0, -1.f, 0, 0, -1.f, 0, 0,
		-1.f, 0, 0, -1.f, 0, 0, -1.f, 0, 0,
		0, -1.f, 0, 0, -1.f, 0, 0, -1.f, 0,
		0, -1.f, 0, 0, -1.f, 0, 0, -1.f, 0,
		0, 1.f, 0, 0, 1.f, 0, 0, 1.f, 0,
		0, 1.f, 0, 0, 1.f, 0, 0, 1.f, 0,
	};

	sizeP = 36 * 3;
	sizeC = 36 * 4;
	sizeN = 36 * 3;

	pos = new GLfloat[sizeP];
	color = new GLfloat[sizeC];
	normals = new GLfloat[sizeN];
	if (isSkybox) {
		std::memcpy(pos, vertexPositions2, sizeof(float) * sizeP);
	}
	else {
		std::memcpy(pos, vertexPositions, sizeof(float) * sizeP);
	}
	std::memcpy(color, vertexColours, sizeof(float) *sizeC);
	std::memcpy(normals, nrmls, sizeof(float) *sizeN);

}

void Cube::createTexture(GLfloat *& texture, GLint & sizeT) {
	/* Manually specified texture coords for our cube */
	GLfloat texcoords[] =
	{
		.25, 0.66,
		0.25, 0.33,
		.5, .33,
		.5, .33,
		0.5, .66,
		.25, 0.66,

		// ace 1 right
		.5, 0.34,
		0.75, 0.34,
		.5, .66,
		0.75, 0.34,
		0.75, .66,
		.50, 0.66,

		// ace 2 front
		0.75, .34,
		1., 0.34,
		0.75, 0.66,
		1., 0.34,
		1., .66,
		0.75, 0.66,

		// ace 3 left
		.0, 0.34,
		0.25, 0.34,
		.0, .66,
		0.25, 0.34,
		0.25, .66,
		.0, .66,

		// ace 4 bottom
		.25, 0.,
		0.50, 0.0,
		.50, .33,
		.50, .33,
		0.25, .33,
		.25, 0.,

		// ace 5 top
		.25, 0.66,
		0.50, 0.66,
		.50, 1.,
		.50, 1.,
		0.25, 1.,
		.25, 0.66,
	};
	sizeT = 36 * 2;

	texture = new GLfloat[sizeT];
	std::memcpy(texture, texcoords, sizeof(float) * sizeT);
}
