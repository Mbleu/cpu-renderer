#include "rasterizer.h"
#include <array>
#include "interpolater.h"

struct Box {
	double left{ 0 };
	double bot{ 0 };
	double right{ 0 };
	double top{ 0 };
};
bool isDegen(const Tri& tri);	// Returns true if a triangle has collinear vertices
Box findBox(const Tri& tri);
bool inTri(const std::array<double, 3>& PBary);

void rasterTri(const Tri& tri, const std::vector<Vecd>& verts, const int xMax, const int yMax, const std::vector<Fragment>& triFrags)
{
	


}
void Rasterizer::rasterTri(const Tri& tri, const TGAColor& color)
{
	if (isDegen(tri)) return;	// skip rasterization if degenerate

	Box box{ findBox(tri) };	// get the tri's bounding box

	Interpolater interpolater(tri.verts);	// interpolater for the triangle to precalculate certain values

	for (int Py{ int(box.bot) }; Py < box.top; ++Py) {			// check each point within the bounding box
		if (Py < 0 || Py >= fragments.size()) continue;			// point lies outside of screen

		for (int Px{ int(box.left) }; Px < box.right; ++Px) {
			if (Px < 0 || Px >= fragments[0].size()) continue;	// point lies outside of screen

			std::array<double, 3> PBary;
			interpolater.barycentric(Px, Py, PBary);

			if (inTri(PBary)) {									// point lies inside tri

				double Pz{ 0 };
				interpolater.sound(PBary, Pz);					// find Pz

				if (Pz < fragments[Py][Px].depth) {				// point is closer than the fragment's depth buffer
					fragments[Py][Px].depth = Pz;
					fragments[Py][Px].color = color;
				}
			}
		}
	}
}
void Rasterizer::rasterEdge(const Vecd& A, const Vecd& B)
{
	const Vecd AB{ B - A };
	const Vecd uAB{ AB.unit() };
	
	for (Vecd ray{ {0, 0, 0} }; abs(ray.mag()) < abs(AB.mag()); ray += uAB) {
		const int Py{ int(A[Axis::y] + ray[Axis::y]) };
		if (Py < 0 || Py >= fragments.size()) continue;		// point lies outside of screen
		const int Px{ int(A[Axis::x] + ray[Axis::x]) };
		if (Px < 0 || Px >= fragments[0].size() ) continue;	// point lies outside of screen
		const double Pz{ A[Axis::z] + ray[Axis::z] };
		if (Pz > fragments[Py][Px].depth) continue;			// point is behind fragment's depth buffer

		fragments[Py][Px].depth = Pz;
		fragments[Py][Px].color = white;
		// this is drawing edges inefficiently since its redraws edges between connected faces
	}
}

Box findBox(const Tri& tri)
{
	using enum Axis;
	double left{ tri.A[x] };
	double bot{ tri.A[y] };
	double right{ tri.A[x] };
	double top{ tri.A[y] };

	for (const Vecd* vert : tri.verts) {					// obtain tri's smallest axis-aligned bounding box
		if ((*vert)[x] < left) left = (*vert)[x];
		if ((*vert)[y] < bot) bot = (*vert)[y];
		if ((*vert)[x] > right) right = (*vert)[x];
		if ((*vert)[y] > top) top = (*vert)[y];
	}

	return Box{ left, bot, right, top };
}
bool isDegen(const Tri& tri)	// Returns true if a triangle has collinear vertices
{
	using enum Axis;
	const Vecd& A{ tri.A };
	const Vecd& B{ tri.B };
	const Vecd& C{ tri.C };
	
	// (Bx - Ax) / (By - Ay) = (Cx - Bx) / (Cy - By)									holds true when the slope of AB is equal to the slope of BC

	if ((B[x] - A[x]) * (C[y] - B[y]) == (C[x] - B[x]) * (B[y] - A[y])) return true;
	else return false;
}
bool inTri(const std::array<double, 3>& PBary)
{
	if (PBary[0] >= 0 && PBary[1] >= 0 && PBary[2] >= 0) return true;
	else return false;
}