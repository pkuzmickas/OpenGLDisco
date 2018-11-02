#include "Camera.h"
using namespace glm;

mat4 Camera::camera = lookAt(
	vec3(-6, 0, 0),
	vec3(0, 0, 0),
	vec3(0, 1, 0)
);

float Camera::speed = 1;

bool Camera::moving[4] = { false, false, false, false };

void Camera::update(float dt) {
	if (moving[FORWARD]) {
		camera = translate(camera, vec3(-speed * dt, 0, 0));
	}
	if (moving[BACKWARD]) {
		camera = translate(camera, vec3(speed * dt, 0, 0));
	}
	if (moving[RIGHT]) {
		camera = translate(camera, vec3(0, 0, -speed * dt));
	}
	if (moving[LEFT]) {
		camera = translate(camera, vec3(0, 0, speed * dt));
	}
}

void Camera::move(movingDir dir, bool isMoving) {
	moving[dir] = isMoving;
}
