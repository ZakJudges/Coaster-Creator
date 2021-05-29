#include "CoasterCamera.h"

void CoasterCamera::update()
{

}

void CoasterCamera::CalculateMatrix(const XMVECTOR& eye, const XMVECTOR& lookat, const XMVECTOR& up, const XMMATRIX& world_matrix)
{
	XMFLOAT3 offset;
	offset.x = XMVectorGetX(world_matrix.r[3]);
	offset.y = XMVectorGetY(world_matrix.r[3]);
	offset.z = XMVectorGetZ(world_matrix.r[3]);
	
	XMVECTOR pos_change = XMLoadFloat3(&offset);
	
	viewMatrix = XMMatrixLookAtLH(eye + pos_change, lookat + pos_change, up);
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
