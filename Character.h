#pragma once
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"
using namespace glm;
class Character {
private:
	enum Parts {
		HEAD,
		BODY,
		LEGL,
		LEGR,
		HANDL,
		HANDR
	};
	struct Transform {
		char type;
		vec3 vec;
	};
	std::vector<vector<Transform>> transforms;
	std::vector<mat4*> bodyParts;
	vec3 curPos;
	int danceStyle = 0;
	bool dancing = false;
	float rot = 30;
	float rotVel;
	mat4 applyTransforms(Parts part, mat4 mat = mat4(1.f));
public:
	Character(Renderer* renderer, vec3 pos, int rgb[2][3]);
	void move(vec3 pos);
	void update(float dt);
	void dance(int style);
	static float danceSpeed;
};