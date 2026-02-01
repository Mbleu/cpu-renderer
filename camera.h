#pragma once
#include "vec.h"

struct Camera {
	Vecd pos{ { 0, 0, 0 } };
	//Vec3d ori{ 0, 0, 0 };		// orientation in Tait-Bryan angles
	double fov{ 1.6 };			// in radians
	double nearClipDist{ 0.1 };
	double farClipDist{ 1000 };
};