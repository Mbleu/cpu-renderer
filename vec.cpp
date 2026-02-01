#include "vec.h"
#include <cmath>

double Vecd::mag() const
{
	double result{ 0 };
	for (const double d : data)
		result += pow(d, 2);

	result = sqrt(result);

	return result;
}
Vecd Vecd::unit() const
{
	double mag_{ mag() };

	Vecd result;
	for (const double d : data)
		result.data.push_back(d / mag_);

	return result;
}
double& Vecd::operator[](const size_t i) { return data[i]; }
double Vecd::operator[](const size_t i) const { return data[i]; }
double& Vecd::operator[](const Axis i) { return (*this)[static_cast<size_t>(i)]; }
double Vecd::operator[](const Axis i) const { return (*this)[static_cast<size_t>(i)]; }
Vecd Vecd::operator -() const
{
	Vecd result;
	for (const double d : data)
		result.data.push_back(-d);

	return result;
}
Vecd& Vecd::operator +=(const Vecd& rhs)
{
	if (rhs.data.size() != data.size()) throw "Vectors must have same dimensions.";

	for (int i{ 0 }; i < data.size(); ++i)
		data[i] += rhs.data[i];

	return *this;
}
Vecd& Vecd::operator -=(const Vecd& rhs)
{
	if (rhs.data.size() != data.size()) throw "Vectors must have same dimensions.";

	for (int i{ 0 }; i < data.size(); ++i)
		data[i] -= rhs.data[i];

	return *this;
}
//Vecd& Vecd::operator *=(const Vecd& rhs)
//{
//	if (rhs.data.size() != data.size()) throw "Vectors must have same dimensions.";
//
//	for (int i{ 0 }; i < data.size(); ++i)
//		data[i] *= rhs.data[i];
//
//	return *this;
//}
Vecd& Vecd::operator *=(const double rhs)
{
	for (double& d : data)
		d *= rhs;

	return *this;
}

Vecd operator +(const Vecd& lhs, const Vecd& rhs)
{
	Vecd result{ lhs };
	result += rhs;
	return result;
}
Vecd operator -(const Vecd& lhs, const Vecd& rhs)
{
	Vecd result{ lhs };
	result -= rhs;
	return result;
}
//Vecd operator *(const Vecd& lhs, const Vecd& rhs)
//{
//	Vecd result{ lhs };
//	result *= rhs;
//	return result;
//}
Vecd operator *(const Vecd& lhs, const double rhs)
{
	Vecd result{ lhs };
	result *= rhs;
	return result;
}
Vecd operator *(const double lhs, const Vecd& rhs)
{
	Vecd result{ rhs };
	result *= lhs;
	return result;
}
double dotprod(const Vecd& lhs, const Vecd& rhs)
{
	if (lhs.dimensions() != rhs.dimensions()) throw "Vectors must have same number of dimensions.";

	double result{ 0 };
	for (int i{ 0 }; i < lhs.data.size(); ++i)
		result += lhs.data[i] * rhs.data[i];

	return result;
}
Vecd xprod(const Vecd& lhs, const Vecd& rhs)
{
	if (lhs.dimensions() != 3 || rhs.dimensions() != 3) throw "Vectors must be 3-dimensional.";

	using enum Axis;

	Vecd result;
	result.data.push_back(lhs[y] * rhs[z] - lhs[z] * rhs[y]);
	result.data.push_back(lhs[z] * rhs[x] - lhs[x] * rhs[z]);
	result.data.push_back(lhs[x] * rhs[y] - lhs[y] * rhs[x]);

	return result;
}