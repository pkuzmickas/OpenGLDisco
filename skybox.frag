// Simple fragment shader for the skybox
// Paulius Kuzmickas October 2018.

#version 420

in vec2 tPos;
out vec4 outputColor;

uniform sampler2D text;

void main()
{
	// Draws the texture
	outputColor = vec4(1-tPos.x, 1-tPos.y, 0, 1);
	outputColor = vec4(texture(text, tPos).xyz/2, 1);
}