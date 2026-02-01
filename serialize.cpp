#include "serialize.h"
#include "objparser.h"

void Serialize::loadDir(const std::string& path_s, std::vector<Model>& models)
{
	for (const auto& entry : std::filesystem::directory_iterator(path_s)) {
		if (entry.path().extension() != ".obj") continue;	// if not .OBJ file, skip

		models.push_back({});								// create a model blueprint
		
		loadFile(entry.path().string(), models.back());
	}
}
void Serialize::loadFile(const std::string& path_s, Model& model)
{
	model.name = std::filesystem::path{ path_s }.stem().string();	// name model after its .OBJ file
	OBJParser parser{ path_s, model };
	parser.parseOBJ();												// read data from .OBJ file
}