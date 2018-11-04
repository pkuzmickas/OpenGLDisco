#pragma once
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
class Camera {
private:
	Camera();
	static bool moving[4];
public:
	static void update(float dt);
	static float speed;
	static mat4 camera;
	static enum movingDir {
		FORWARD,
		RIGHT,
		BACKWARD,
		LEFT
	};
	static void move(movingDir dir, bool isMoving);
	static float camMovedAmount;

};