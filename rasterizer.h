#pragma once
#include "fragment.h"
#include "mesh.h"
#include <vector>

void rasterTri(const Tri& tri, const std::vector<Vecd>& verts, const int xMax, const int yMax, const std::vector<Fragment>& triFrags);
void rasterEdge(const Vecd& A, const Vecd& B);