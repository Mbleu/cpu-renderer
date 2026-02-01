#pragma once
#include <vector>

enum class Axis { x, y, z, w };

struct Vecd {
	std::vector<double> data;

	int dimensions() const { return int(data.size()); }
	double mag() const;	// magnitude of vector
	Vecd unit() const;	// unit vector
	double& operator[](const size_t i);
	double operator[](const size_t i) const;
	double& operator[](const Axis i);
	double operator[](const Axis i) const;
	Vecd operator -() const;
	Vecd& operator +=(const Vecd& rhs);
	Vecd& operator -=(const Vecd& rhs);
	//Vecd& operator *=(const Vecd& rhs);	// dot product
	Vecd& operator *=(const double rhs);
};

Vecd operator +(const Vecd& lhs, const Vecd& rhs);
Vecd operator -(const Vecd& lhs, const Vecd& rhs);
//Vecd operator *(const Vecd& lhs, const Vecd& rhs);
Vecd operator *(const Vecd& lhs, const double rhs);
Vecd operator *(const double lhs, const Vecd& rhs);
double dotprod(const Vecd& lhs, const Vecd& rhs);
Vecd xprod(const Vecd& lhs, const Vecd& rhs);	// cross product