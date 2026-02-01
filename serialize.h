#pragma once
#include "model.h"
#include <filesystem>
#include <vector>

namespace Serialize {
	void loadDir(const std::string& path_s, std::vector<Model>& models);
	void loadFile(const std::string& path_s, Model& model);
}