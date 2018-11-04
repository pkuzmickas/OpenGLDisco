// Basic vertex shader with a main purpose to set the object's position and calculate values for lighting
// Paulius Kuzmickas October 2018
#version 400 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec3 normal;

vec4 ambient = vec4(0.2 * color.x, 0.2 * color.y, 0.2 * color.z, 1);
vec4 specular = vec4(0.6 * color.x, 0.6 * color.y, 0.6 * color.z, 1);
vec4 diffuse = vec4(0.4 * color.x, 0.4 * color.y, 0.4 * color.z, 1);

uniform vec4 light;
uniform mat4 model, view, projection;

out vec3 fLight, fNormal, fPosition;
out vec4 fDiffuse, fAmbient, fSpecular;

void main()
{	
	fDiffuse = diffuse;
	fAmbient = ambient;
	fSpecular = specular;

	fPosition = (view * model * position).xyz;

	fLight = (view * light).xyz;

	fNormal = transpose(inverse(mat3(view * model)))*normal;

	gl_Position = projection * view * model * position;
}