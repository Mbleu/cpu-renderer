#pragma once
#include "vec.h"
#include "tgaimage.h"
#include "matrix.h"
#include "camera.h"
#include <array>
#include <vector>
#include <string>

struct Tri {
	const std::array<int, 3> vertIndices;
};

class Face {
public:
	Face(const std::vector<int>& vertIndices);
	const std::vector<int>& getVertIndices() const;
	const std::vector<Tri>& getTris() const;

private:
	std::vector<int> vertIndices;
	std::vector<Tri> tris;
};

struct Edge {
	const int AIndex;
	const int BIndex;
};

class Mesh {
public:
	void addVert(const Vecd& vert);
	void addEdge(const int AIndex, const int BIndex);
	void addFace(const std::vector<int>& vertIndices);
	void transform(const Matrix& M);

	const std::vector<Vecd>& getVerts() const;
	const std::vector<Face>& getFaces() const;
	const std::vector<Edge>& getEdges() const;
	int dimensions() const;
	Vecd centroid() const;

private:
	std::vector<Vecd> verts;
	std::vector<Edge> edges;
	std::vector<Face> faces;
};