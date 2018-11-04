// Minimal fragment shader

#version 400 core

in vec3 fposition, fnormal, flightpos;
in vec4 fdiffuse, fspecular, fambient;

out vec4 outputColor;

void main()
{
	vec3 to_light = flightpos - fposition;
	float distance_to_light = length(to_light);
	to_light = normalize(to_light);
	vec3 fnormal_n = normalize(fnormal);

	//diffuse
	vec4 diffuse = max(dot(fnormal_n, to_light), 0) * fdiffuse;
	
	//specular
	vec3 normalised_vert = normalize(-fposition.xyz);
	vec3 reflection = reflect(-to_light, fnormal_n);
	vec4 specular = pow(max(dot(reflection, normalised_vert), 0), 50) * fspecular;
	
	float k1 = .1;
	float attenuation = 1.0 / (k1 + k1*distance_to_light + k1*pow(distance_to_light, 2));
	

	outputColor = attenuation*(diffuse + specular) + fambient;
}