#pragma once

#include "../DXFramework/Camera.h"

class CoasterCamera : public Camera
{
public:
	void Update();
	void CalculateMatrix(const XMVECTOR& eye, const XMVECTOR& lookat, const XMVECTOR& up, const XMMATRIX& world_matrix);
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