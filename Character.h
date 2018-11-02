#pragma once
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"
using namespace glm;
class Character {
private:
	Character();
public:
	static void createCharacter(Renderer* renderer, vec3 pos);
};