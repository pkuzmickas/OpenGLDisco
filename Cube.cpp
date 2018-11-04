/* Cube.cpp
 Static class to control the creation of a cube.
 Paulius Kuzmickas October 2018.
*/
#include "Cube.h"

/*
	Static function to create the cube vertices etc. and return them as vars pos, color, etc.
*/
void Cube::createCube(int rgb[3], GLfloat*& pos, GLfloat*& color, GLfloat*& normals, GLint& sizeP, GLint& sizeC, GLint& sizeN, bool isSkybox) {
	
	/*
		Its possible to specify the color of a cube and it will be applied.
	*/
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

	/*
		If the cube is for the skybox, it will have different vertex positions.
		This has been done to avoid the black lines at the corners for mixing pixels.
	*/

	if (isSkybox) {
		GLfloat vertexPositions[] = {
		-1.f, 1.f, -.99f,
		-1.f, -1.f, -.99f,
		1.f, -1.f, -.99f,

		1.f, -1.f, -.99f,
		1.f, 1.f, -.99f,
		-1.f, 1.f, -.99f,

		0.99f, -1.f, -1.f,
		0.99f, -1.f, 1.f,
		0.99f, 1.f, -1.f,

		0.99f, -1.f, 1.f,
		0.99f, 1.f, 1.f,
		0.99f, 1.f, -1.f,

		1.f, -1.f, 0.99f,
		-1.f, -1.f, 0.99f,
		1.f, 1.f, 0.99f,

		-1.f, -1.f, 0.99f,
		-1.f, 1.f, 0.99f,
		1.f, 1.f, 0.99f,

		-.99f, -1.f, 1.f,
		-.99f, -1.f, -1.f,
		-.99f, 1.f, 1.f,

		-.99f, -1.f, -1.f,
		-.99f, 1.f, -1.f,
		-.99f, 1.f, 1.f,

		-1.f, -1.f, 1.f,
		1.f, -1.f, 1.f,
		1.f, -1.f, -1.f,

		1.f, -1.f, -1.f,
		-1.f, -1.f, -1.f,
		-1.f, -1.f, 1.f,

		-1.f, 1.f, -1.f,
		1.f, 1.f, -1.f,
		1.f, 1.f, 1.f,

		1.f, 1.f, 1.f,
		-1.f, 1.f, 1.f,
		-1.f, 1.f, -1.f,
		};

		std::memcpy(pos, vertexPositions, sizeof(float) * sizeP);
	}
	else {
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
		std::memcpy(pos, vertexPositions, sizeof(float) * sizeP);
	}
	std::memcpy(color, vertexColours, sizeof(float) *sizeC);
	std::memcpy(normals, nrmls, sizeof(float) *sizeN);

}

/*
	Function to create the coordinates for the texture.
	Returns the texture array and the size of it.
*/
void Cube::createTexture(GLfloat *& texture, GLint & sizeT) {
	/* Manually specified texture coords for our cube */
	GLfloat textureCoords[] =
	{
		.25, 0.66,
		0.25, 0.33,
		.5, .33,
		.5, .33,
		0.5, .66,
		.25, 0.66,

		.5, 0.34,
		0.75, 0.34,
		.5, .66,
		0.75, 0.34,
		0.75, .66,
		.50, 0.66,

		0.75, .34,
		1., 0.34,
		0.75, 0.66,
		1., 0.34,
		1., .66,
		0.75, 0.66,

		.0, 0.34,
		0.25, 0.34,
		.0, .66,
		0.25, 0.34,
		0.25, .66,
		.0, .66,

		.25, 0.,
		0.50, 0.0,
		.50, .33,
		.50, .33,
		0.25, .33,
		.25, 0.,

		.25, 0.66,
		0.50, 0.66,
		.50, 1.,
		.50, 1.,
		0.25, 1.,
		.25, 0.66,
	};
	sizeT = 36 * 2;

	texture = new GLfloat[sizeT];
	std::memcpy(texture, textureCoords, sizeof(float) * sizeT);
}
