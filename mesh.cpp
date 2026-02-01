#include "mesh.h"
#include <fstream>
#include <sstream>

Face::Face(const std::vector<int>& vertIndices)
	: vertIndices(vertIndices)
{
	if (vertIndices.size() < 3) throw "Face must have at least 3 vertices.";

	for (int i{ 1 }; i < vertIndices.size(); ++i)
		tris.push_back({ {0, i, (i + 1) % int(vertIndices.size())} });	// creates a fan triangulation (stores indices relative to face)
}
const std::vector<int>& Face::getVertIndices() const
{
	return vertIndices;
}
const std::vector<Tri>& Face::getTris() const
{
	return tris;
}

void Mesh::addVert(const Vecd& vert)
{
	verts.push_back(vert);
}
void Mesh::addEdge(const int AIndex, const int BIndex)
{
	for (const Edge& edge : edges) {	// check if the edge already exists before adding
		if (edge.AIndex == AIndex && edge.BIndex == BIndex) return;
		if (edge.AIndex == BIndex && edge.BIndex == AIndex) return;
	}

	edges.push_back({ AIndex, BIndex });
}
void Mesh::addFace(const std::vector<int>& vertIndices)
{
	if (vertIndices.size() < 3) throw "Face must have at least 3 vertices.";

	faces.push_back({ {vertIndices} });
	for (int i{ 0 }; i < vertIndices.size(); ++i)
		addEdge(vertIndices[i], vertIndices[(i + 1) % vertIndices.size()]);
}
void Mesh::transform(const Matrix& M)
{
	for (Vecd& vert : verts) {
		vert.data.push_back(1);										// homogenise vector
		Matrix vertMat{ 1, vert.data };								// convert vector to matrix
		vertMat = M * vertMat;										// transform
		vertMat *= 1 / vertMat.copyElem(vertMat.rowCount() - 1, 0);	// divide each dimension by the extra dimension
		vert.data = vertMat.copyCol(0);								// convert matrix back to vector
		vert.data.pop_back();										// remove extra dimension
	}
}

const std::vector<Vecd>& Mesh::getVerts() const
{
	return verts;
}
const std::vector<Edge>& Mesh::getEdges() const
{
	return edges;
}
const std::vector<Face>& Mesh::getFaces() const
{
	return faces;
}
int Mesh::dimensions() const
{
	if (verts.size() == 0) throw "Mesh has no dimensions.";

	return verts.front().dimensions();
}
Vecd Mesh::centroid() const
{
	Vecd centroid_{ std::vector<double>(dimensions()) };
	for (const Vecd& vert : verts)
		centroid_ += vert;
	centroid_ *= (1. / verts.size());
	return centroid_;
}