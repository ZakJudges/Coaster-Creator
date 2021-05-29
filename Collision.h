#pragma once

#include "../Spline-Library/vector.h"

class Collision
{
public: 
	static bool PointInSphere(SL::Vector& sphere_centre, const float sphere_radius, SL::Vector& point) ;
	static bool RayInSphere(SL::Vector& ray_start, SL::Vector& ray_direction, const float sphere_radius, SL::Vector& sphere_centre);

};