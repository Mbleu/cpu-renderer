#pragma once
#include "scene.h"

class Controller {
public:
	Controller(Scene& scene);

private:
	Scene& scene;
	const std::vector<Model>* const blueprints;
};