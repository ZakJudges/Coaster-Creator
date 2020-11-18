#pragma once

#include "../Spline-Library/vector.h"

class Collision
{
public: 
	Collision();
	bool PointInSphere(const SL::Vector& sphere_centre, const float sphere_radius, const SL::Vector& point) const;
	bool RayInSphere(const SL::Vector& ray_start, const SL::Vector& ray_direction, const float sphere_radius, const SL::Vector& sphere_centre);
};