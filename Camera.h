/* Camera.h
 Static class to control and update the camera.
 Paulius Kuzmickas October 2018.
*/

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
	// Variable to see how much has the camera moved
	static float camMovedAmount;

};