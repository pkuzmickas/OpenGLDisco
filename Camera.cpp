#include "Camera.h"
using namespace glm;

mat4 Camera::camera = lookAt(
	vec3(-8, 1, 0),
	vec3(0, 0, 0),
	vec3(0, 1, 0)
);

float Camera::speed = 10;

bool Camera::moving[4] = { false, false, false, false };

void Camera::update(float dt) {
	if (moving[FORWARD]) {
		vec3 forward(camera[0][2], camera[1][2], camera[2][2]);
		vec3 strafe(camera[0][0], camera[1][0], camera[2][0]);
		vec3 movement = ( forward ) * speed * dt;

		//camera = translate(camera, vec3(-speed * dt, 0, 0));
		camera = translate(camera, vec3(movement.x, movement.y, movement.z));
	}
	else if (moving[BACKWARD]) {
		//camera = translate(camera, vec3(speed * dt, 0, 0));
		vec3 forward(camera[0][2], camera[1][2], camera[2][2]);
		vec3 strafe(camera[0][0], camera[1][0], camera[2][0]);
		vec3 movement = (-forward ) * speed * dt;

		camera = translate(camera, vec3(movement.x, movement.y, movement.z));
	}
	else if (moving[RIGHT]) {
		Camera::camera = translate(Camera::camera, vec3(1, 0, 0));
		Camera::camera = rotate(Camera::camera, radians(-90 * dt), vec3(0, 1, 0));
		Camera::camera = translate(Camera::camera, vec3(-1, 0, 0));
	}
	else if (moving[LEFT]) {
		Camera::camera = translate(Camera::camera, vec3(1, 0, 0));
		Camera::camera = rotate(Camera::camera, radians(90 * dt), vec3(0, 1, 0));
		Camera::camera = translate(Camera::camera, vec3(-1, 0, 0));
	}

}

void Camera::move(movingDir dir, bool isMoving) {
	moving[dir] = isMoving;
}
