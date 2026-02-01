#pragma once
#include "vec.h"
#include <array>

class Interpolater {
public:
	Interpolater(const std::array<Vecd*, 3>& verts);
	void barycentric(const double Px, const double Py, std::array<double, 3>& PBary);
	void sound(const std::array<double, 3>& PBary, double& Pz);

private:
	const std::array<Vecd*, 3>& verts;
	const Vecd AB;
	const Vecd AC;
	const double baryCalcDenom;
};