#version 420

layout(location = 0) in vec4 position;
layout(location = 3) in vec2 texPos;
uniform mat4 model, view, projection;

out vec2 tPos;

void main()
{	
	tPos = texPos;
	gl_Position = projection * view * model * position;
}