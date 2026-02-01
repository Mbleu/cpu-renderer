#pragma once
#include "mesh.h"
#include <string>

struct Model {
	std::string name{ "" };
	Mesh mesh;
	bool showFaces{ true };
	bool showEdges{ true };
	TGAColor color{ 255, 0, 255, 255 };
};