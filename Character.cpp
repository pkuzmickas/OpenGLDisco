#include "Character.h"
using namespace glm;
void Character::createCharacter(Renderer* renderer, vec3 pos) {
	int headColor[3] = { 255,224,189 };
	mat4* head = renderer->createObject(Renderer::Objects::CUBE, headColor);
	*head = translate(*head, vec3(0, 0.50 * 0.6f, 0));
	*head = scale(*head, vec3(0.6f, 0.6f, 0.6f));
	int bodyColor[3] = { 0,0,140 };
	mat4* body = renderer->createObject(Renderer::Objects::CUBE, bodyColor);
	*body = translate(*body, vec3(0, 0, 0));
	int pantsColor[3] = { 166,67,1 };
	mat4* legl = renderer->createObject(Renderer::Objects::CUBE, pantsColor);
	*legl = translate(*legl, vec3(0, -0.4f * 1.5f, -0.25f*0.5f));
	*legl = scale(*legl, vec3(0.5f, 1.5f, 0.5f));
	mat4* legr = renderer->createObject(Renderer::Objects::CUBE, pantsColor);
	*legr = translate(*legr, vec3(0, -0.4f * 1.5f, 0.25f*0.5f));
	*legr = scale(*legr, vec3(0.5f, 1.5f, 0.5f));
	
}
