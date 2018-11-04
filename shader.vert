// Vertex shader with a model transformation uniform

#version 400 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec3 normal;

vec4 ambient_colour = vec4(0.2 * color.x, 0.2 * color.y, 0.2 * color.z, 1);
vec4 diffuse_colour = vec4(0.4 * color.x, 0.4 * color.y, 0.4 * color.z, 1);
vec4 specular_colour = vec4(0.6 * color.x, 0.6 * color.y, 0.6 * color.z, 1);

out vec3 fposition, fnormal, flightpos;
out vec4 fdiffuse, fspecular, fambient;

uniform vec4 light;
uniform mat4 model, view, projection;

void main()
{
	fposition = (view * model * position).xyz;
	fnormal = transpose(inverse(mat3(view * model)))*normal;
	flightpos = (view * light).xyz;
	fdiffuse = diffuse_colour;
	fambient = ambient_colour;
	fspecular = specular_colour;

	gl_Position = projection * view * model * position;
}