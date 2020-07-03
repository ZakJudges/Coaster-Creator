#pragma once

#include "../DXFramework/Camera.h"

class CoasterCamera : public Camera
{
public:
	void update();

	void moveForward();
	void moveBackward();
	void moveUpward();
	void moveDownward();
	void turnLeft();
	void turnRight();
	void turnUp();
	void turnDown();
	void strafeRight();
	void strafeLeft();
	void turn(int x, int y);
};