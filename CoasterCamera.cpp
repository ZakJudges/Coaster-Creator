#include "CoasterCamera.h"

void CoasterCamera::update()
{

}

void CoasterCamera::CalculateMatrix(XMVECTOR eye, XMVECTOR lookat, XMVECTOR up)
{
	viewMatrix = XMMatrixLookAtLH(eye, lookat, up);
}

void CoasterCamera::moveForward()
{
}

void CoasterCamera::moveBackward()
{
}

void CoasterCamera::moveUpward()
{
}

void CoasterCamera::moveDownward()
{
}

void CoasterCamera::turnLeft()
{
}

void CoasterCamera::turnRight()
{
}

void CoasterCamera::turnUp()
{
}

void CoasterCamera::turnDown()
{
}

void CoasterCamera::strafeRight()
{
}

void CoasterCamera::strafeLeft()
{
}

void CoasterCamera::turn(int x, int y)
{
}
