#include "Character.h"
using namespace glm;

Character::Character(Renderer * renderer, vec3 pos) {
	int headColor[3] = { 255,224,189 };
	mat4* head = renderer->createObject(Renderer::Objects::CUBE, headColor);
	//*head = translate(*head, vec3(0, 0.50 * 0.6f, 0));
	//*

	*head = translate(*head, vec3(0 + pos.x, 0.4f + pos.y, 0 + pos.z));
	*head = scale(*head, vec3(0.6f, 0.6f, 0.75f));

	int bodyColor[3] = { 0,0,140 };
	mat4* body = renderer->createObject(Renderer::Objects::CUBE, bodyColor);
	*body = translate(*body, vec3(0 + pos.x, 0 + pos.y, 0 + pos.z));
	*body = scale(*body, vec3(0.2f, 1, 0.75f));

	int pantsColor[3] = { 166,67,1 };
	mat4* legl = renderer->createObject(Renderer::Objects::CUBE, pantsColor);
	/**legl = translate(*legl, vec3(0, -0.2f, 0));
	*legl = rotate(*legl, radians(-30.f), vec3(0, 0, 1));
	*legl = translate(*legl, vec3(0, 0.2f, 0));*/
	*legl = translate(*legl, vec3(0 + pos.x, -0.546f + pos.y, -0.22f * 0.4f + pos.z));
	*legl = scale(*legl, vec3(0.2f, 1.2f, 0.4f));

	mat4* legr = renderer->createObject(Renderer::Objects::CUBE, pantsColor);
	*legr = translate(*legr, vec3(0 + pos.x, -0.546f + pos.y, 0.22f*0.4f + pos.z));
	*legr = scale(*legr, vec3(0.2f, 1.2f, 0.4f));

	mat4* handl = renderer->createObject(Renderer::Objects::CUBE, bodyColor);
	*handl = translate(*handl, vec3(0, 0.2f, 0));
	*handl = rotate(*handl, radians(210.f), vec3(0, 0, 1));
	*handl = translate(*handl, vec3(0, -0.2f, 0));
	*handl = translate(*handl, vec3(0 + pos.x, -0.05f + pos.y, -0.286f + pos.z));
	*handl = scale(*handl, vec3(0.2f, 1.2f, 0.4f));

	mat4* handr = renderer->createObject(Renderer::Objects::CUBE, bodyColor);
	*handr = translate(*handr, vec3(0 + pos.x, -0.05f + pos.y, 0.286f + pos.z));
	*handr = scale(*handr, vec3(0.2f, 1.2f, 0.4f));
}
