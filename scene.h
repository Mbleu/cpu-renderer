#pragma once
#include "camera.h"
#include "model.h"
#include <vector>

struct Scene {
	Camera cam{ {{0, 0, 0}} };
	std::vector<Model> models;
};