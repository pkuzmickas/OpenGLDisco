// Basic fragment shader with diffuse and specular lighting

#version 400 core

in vec3 fLight, fNormal, fPosition;
in vec4 fDiffuse, fAmbient, fSpecular;

out vec4 outputColor;

void main()
{
	// Light distance and direction
	vec3 vecToLight = fLight - fPosition;
	float distToLight = length(vecToLight);
	vecToLight = normalize(vecToLight);

	vec3 fNormalN = normalize(fNormal);

	// Diffue lighting calculations
	vec4 diffuse = max(dot(fNormalN, vecToLight), 0) * fDiffuse;
	
	// Specular lighting calculations
	vec3 posNormalised = normalize(-fPosition.xyz);
	vec3 reflection = reflect(-vecToLight, fNormalN);
	vec4 specular = pow(max(dot(reflection, posNormalised), 0), 50) * fSpecular;
	
	// Attenuation effect calculations
	float k1 = .1;
	float attenuation = 1.0 / (k1 + k1*distToLight + k1*pow(distToLight, 2));
	
	outputColor = attenuation*(diffuse + specular) + fAmbient;
}