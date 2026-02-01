#pragma once
#include "vec.h"
#include "matrix.h"
#include "camera.h"

void translate(const Vecd& transVec, Matrix& M);
void translate(const double transVal, Axis axis, Matrix& M);
void scale(const Vecd& scaleVec, Matrix& M);
void scale(const double scaleVal, Matrix& M);
void rotate(const double degrees, const int throughPlaneAxisA, const int throughPlaneAxisB, Matrix& M);
void rotate(const double degrees, Axis aboutAxis, Matrix& M);	// 3-dimensional rotation about an axis
//void shear(const double d, Axis axis, Matrix& M);
//void reflect(const double angle, Axis axis, Matrix& M);
void perspective(const Camera& cam, const double aspectRatio, Matrix& M);