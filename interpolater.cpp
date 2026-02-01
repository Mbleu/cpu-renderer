#include "interpolater.h"

using enum Axis;

Interpolater::Interpolater(const std::array<Vecd*, 3>& verts)
	: verts{ verts },
	AB{ *verts[1] - *verts[0] }, AC{ *verts[2] - *verts[0] },
	baryCalcDenom{ AB[x] * AC[y] - AB[y] * AC[x] }
{}

void Interpolater::barycentric(const double Px, const double Py, std::array<double, 3>& PBary)
{
	const double APx{ Px - (*verts[0])[x] };
	const double APy{ Py - (*verts[0])[y] };

	if (AB[x] > 0 && AB[y] > 0) {
		PBary[2] = (APy * AB[x] - APx * AB[y]) / baryCalcDenom;
		PBary[1] = (APx - PBary[2] * AC[x]) / AB[x];
	}
	else {
		PBary[1] = (APx * AC[y] - APy * AC[x]) / baryCalcDenom;
		PBary[2] = (APx - PBary[1] * AB[x]) / AC[x];
	}
	PBary[0] = 1 - PBary[1] - PBary[2];
}
void Interpolater::sound(const std::array<double, 3>& PBary, double& Pz)
{
	Pz = PBary[1] * AB[z] + PBary[2] * AC[z];
}