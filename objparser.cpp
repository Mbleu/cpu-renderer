#include "objparser.h"

OBJParser::OBJParser(const std::string& path_s, Model& model)
	: path(path_s), model(model)
{}
void OBJParser::parseOBJ()
{
	std::ifstream ifs{ path };
	std::string line;
	while (std::getline(ifs, line)) {		// read line by line until EOF
		std::istringstream iss_line(line);	// convert line to input stream
		parseLine(iss_line);
	}

	if (model.mesh.getVerts().empty()) throw "No vertices found.";
}
void OBJParser::parseLine(std::istringstream& iss_line)
{
	std::string type;
	iss_line >> type;			// read line type (vertex, face, normal, ...)

	if (type == "v")			// vertex
		parseVertex(iss_line);
	else if (type == "f")		// face
		parseFace(iss_line);
}
void OBJParser::parseVertex(std::istringstream& iss_vertex)
{
	Vecd vertex;
	for (double d{ 0 }; iss_vertex >> d; vertex.data.push_back(d));	// read data into vertex
	model.mesh.addVert(vertex);										// add vertex to mesh
}
void OBJParser::parseFace(std::istringstream& iss_face)
{
	std::vector<int> vertIndices;
	std::string group;
	while (iss_face >> group) {					// read group by group
		std::istringstream iss_group(group);	// convert group to input stream
		parseFaceGroup(iss_group, vertIndices);
	}

	if (vertIndices.size() < 3) throw "Face must have at least 3 vertices.";
	model.mesh.addFace(vertIndices);
}
void OBJParser::parseFaceGroup(std::istringstream& iss_group, std::vector<int>& vertIndices)
{
	std::string s_index;

	enum indices { vertex, texture, normal };							// ordered types of indices within a group

	for (int i{ 0 }; std::getline(iss_group, s_index, '/'); ++i) {		// read index data from group into a string
		switch (i) {													// type of index
		case vertex:
		{
			int vert_index{ std::stoi(s_index) };						// convert vertex index from string to int
			vertIndices.push_back(vert_index - 1);						// add vertex to face (-1 because .OBJ indices start at 1)
			break;
		}
		case texture:
		{
			break;
		}
		case normal:
		{
			break;
		}
		default:
			throw "Group has too many indices.";
		}
	}
}