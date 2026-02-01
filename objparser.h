#pragma once
#include "model.h"
#include <string>
#include <filesystem>

class OBJParser {
public:
	OBJParser(const std::string& path_s, Model& model);
	void parseOBJ();
	void parseLine(std::istringstream& iss_line);
	void parseVertex(std::istringstream& iss_vertex);
	void parseFace(std::istringstream& iss_face);
	void parseFaceGroup(std::istringstream& iss_group, std::vector<int>& vertIndices);

private:
	const std::filesystem::path path;
	Model& model;
};