/* Character.cpp
 Class responsible for creating and controlling a character.
 Paulius Kuzmickas October 2018.
*/
#include "Character.h"
using namespace glm;

float Character::danceSpeed = 250;

/*
	Function which applies the collected transformations onto a matrix.
*/
mat4 Character::applyTransforms(Parts part, mat4 mat) {
	mat4 res = mat;
	for (auto t : transforms[part]) {
		switch (t.type) {
		case 't': {
			res = translate(res, t.vec);
			break;
		}
		case 's': {
			res = scale(res, t.vec);
			break;
		}
		}
	}
	return res;
}

/*
	Constructor, where I create the character's body.
	All the transformations are pushed onto a vector so that they could be reapplied later.
*/
Character::Character(Renderer * renderer, vec3 pos, int rgb[2][3]) {

	for (int i = 0; i < 6; i++) {
		vector<Transform> transform;
		transforms.push_back(transform);
		bodyParts.push_back(NULL);
	}

	int headColor[3] = { 255,224,189 };
	mat4* head = renderer->createObject(Renderer::Objects::CUBE, headColor);

	vec3 vec = vec3(0 + pos.x, 0.4f + pos.y, 0 + pos.z);
	*head = translate(*head, vec);
	transforms[HEAD].push_back({ 't', vec });
	vec = vec3(0.6f, 0.6f, 0.75f);
	*head = scale(*head, vec);
	transforms[HEAD].push_back({ 's', vec });
	bodyParts[HEAD] = head;

	int bodyColor[3];
	for (int i = 0; i < 3; i++) bodyColor[i] = rgb[0][i];
	mat4* body = renderer->createObject(Renderer::Objects::CUBE, bodyColor);
	vec = vec3(0 + pos.x, 0 + pos.y, 0 + pos.z);
	*body = translate(*body, vec);
	transforms[BODY].push_back({ 't', vec });
	vec = vec3(0.2f, 1, 0.75f);
	*body = scale(*body, vec);
	transforms[BODY].push_back({ 's', vec });

	bodyParts[BODY] = body;

	int pantsColor[3];
	for (int i = 0; i < 3; i++) pantsColor[i] = rgb[1][i];
	mat4* legl = renderer->createObject(Renderer::Objects::CUBE, pantsColor);
	/**legl = translate(*legl, vec3(0, -0.2f, 0));
	*legl = rotate(*legl, radians(-30.f), vec3(0, 0, 1));
	*legl = translate(*legl, vec3(0, 0.2f, 0));*/
	vec = vec3(0 + pos.x, -0.546f + pos.y, -0.22f * 0.4f + pos.z);
	*legl = translate(*legl, vec);
	transforms[LEGL].push_back({ 't', vec });
	vec = vec3(0.2f, 1.2f, 0.4f);
	*legl = scale(*legl, vec);
	transforms[LEGL].push_back({ 's', vec });


	bodyParts[LEGL] = legl;

	mat4* legr = renderer->createObject(Renderer::Objects::CUBE, pantsColor);
	vec = vec3(0 + pos.x, -0.546f + pos.y, 0.22f*0.4f + pos.z);
	*legr = translate(*legr, vec);
	transforms[LEGR].push_back({ 't', vec });
	vec = vec3(0.2f, 1.2f, 0.4f);
	*legr = scale(*legr, vec);
	transforms[LEGR].push_back({ 's', vec });

	bodyParts[LEGR] = legr;

	mat4* handl = renderer->createObject(Renderer::Objects::CUBE, bodyColor);
	/**handl = translate(*handl, vec3(0, 0.2f, 0));
	*handl = rotate(*handl, radians(210.f), vec3(0, 0, 1));
	*handl = translate(*handl, vec3(0, -0.2f, 0));*/
	vec = vec3(0 + pos.x, -0.05f + pos.y, -0.286f + pos.z);
	*handl = translate(*handl, vec);
	transforms[HANDL].push_back({ 't', vec });
	vec = vec3(0.2f, 1.2f, 0.4f);
	*handl = scale(*handl, vec);
	transforms[HANDL].push_back({ 's', vec });

	bodyParts[HANDL] = handl;

	mat4* handr = renderer->createObject(Renderer::Objects::CUBE, bodyColor);
	vec = vec3(0 + pos.x, -0.05f + pos.y, 0.286f + pos.z);
	*handr = translate(*handr, vec);
	transforms[HANDR].push_back({ 't', vec });
	vec = vec3(0.2f, 1.2f, 0.4f);
	*handr = scale(*handr, vec);
	transforms[HANDR].push_back({ 's', vec });

	bodyParts[HANDR] = handr;

	rotVel = Character::danceSpeed;
}
/*
	Function to translate the character's position.
	Takes into consideration the scale of different body parts.
*/
void Character::move(vec3 pos) {
	curPos = pos;
	for (int i = 0; i < bodyParts.size(); i++) {
		auto part = bodyParts[i];
		if (i == HEAD) {
			vec3 vec = vec3(pos.x / 3, pos.y, pos.z);
			*part = translate(*part, vec);
			transforms[HEAD].push_back({ 't', vec });
			
		}
		else if (i != BODY) {
			vec3 vec = vec3(pos.x, pos.y, pos.z* 1.875f);
			*part = translate(*part, vec);
			transforms[i].push_back({ 't', vec });
		}
		else {
			*part = translate(*part, pos);
			transforms[i].push_back({ 't', pos });
		}
		
	}
}
/*
	Update function which is called every frame.
	Updates the dance moves.
*/
void Character::update(float dt) {
	if (dancing) {
		if (danceStyle == 0) {
			int rot2 = -rot;

			auto handl = bodyParts[HANDL];
			*handl = mat4(1.f);
			*handl = translate(*handl, vec3(0.2f * curPos.x, 0.2f, 0));
			*handl = rotate(*handl, radians(rot2 *1.f), vec3(0, 0, 1));
			*handl = translate(*handl, vec3(-0.2f * curPos.x, -0.2f, 0));
			*handl = applyTransforms(HANDL, *handl);
			auto handr = bodyParts[HANDR];
			*handr = mat4(1.f);
			*handr = translate(*handr, vec3(0.2f * curPos.x, 0.2f, 0));
			*handr = rotate(*handr, radians(rot *1.f), vec3(0, 0, 1));
			*handr = translate(*handr, vec3(-0.2f * curPos.x, -0.2f, 0));
			*handr = applyTransforms(HANDR, *handr);
			
			rot += rotVel * dt;
			if (rot > 60 || rot < -60) {
				if (rot > 60) rot = 60; else rot = -60;
				rotVel *= -1;
				rotVel = rotVel < 0 ? -Character::danceSpeed : Character::danceSpeed;
				
			}

		}
	}
}

/*
	Activates the dancing and sets the style type.
*/
void Character::dance(int style) {
	danceStyle = style;
	dancing = true;
}
