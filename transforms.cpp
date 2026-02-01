#include "transforms.h"
#include <numbers>

double toRad(const double degrees)
{
	return degrees * (std::numbers::pi_v<float> / 180.);
}

void translate(const Vecd& transVec, Matrix& M)
{
	if (transVec.dimensions() + 1 != M.rowCount()) throw "Incompatible dimensions.";

	Matrix transMat{ Matrix::identity(M.rowCount()) };

	for (int i{ 0 }; i < transVec.dimensions(); ++i)
		transMat.setElem(i, transMat.colCount() - 1, transVec[i]);

	M = transMat * M;
}
void translate(const double transVal, Axis axis, Matrix& M)
{
	if (static_cast<int>(axis) >= M.rowCount() - 1) throw "Axis dimension too high.";

	Matrix transMat{ Matrix::identity(M.rowCount()) };

	transMat.setElem(static_cast<int>(axis), transMat.colCount() - 1, transVal);

	M = transMat * M;
}
void scale(const Vecd& scaleVec, Matrix& M)
{
	if (scaleVec.dimensions() + 1 != M.rowCount()) throw "Incompatible dimensions.";

	Matrix scaleMat{ Matrix::identity(M.rowCount()) };

	for (int i{ 0 }; i < scaleVec.dimensions(); ++i)
		scaleMat.setElem(i, i, scaleVec[i]);

	M = scaleMat * M;
}
void scale(const double scaleVal, Matrix& M)
{
	Matrix scaleMat{ Matrix::identity(M.rowCount()) };

	for (int i{ 0 }; i < scaleMat.colCount() - 1; ++i)
		scaleMat.setElem(i, i, scaleVal);

	M = scaleMat * M;
}
void rotate(const double degrees, const int throughPlaneAxisA, const int throughPlaneAxisB, Matrix& M)	// n-dimensional rotation through single plane
{
	if (throughPlaneAxisA < 0 || throughPlaneAxisB < 0) throw "Dimensions cannot be negative.";
	if (throughPlaneAxisA >= M.rowCount() - 1 || throughPlaneAxisB >= M.rowCount() - 1) throw "Cannot rotate through these dimensions.";
	if (throughPlaneAxisA == throughPlaneAxisB) throw "Axes must be different to describe a rotation plane.";


	double radians{ toRad(degrees) };
	Matrix rotMat{ Matrix::identity(M.rowCount()) };

	rotMat.setElem(throughPlaneAxisA, throughPlaneAxisA, cos(radians));		// note there is no "hand rule" outside of 3d, the direction of rotation is determined by the order in which the axes of the plane are given
	rotMat.setElem(throughPlaneAxisA, throughPlaneAxisB, -sin(radians));
	rotMat.setElem(throughPlaneAxisB, throughPlaneAxisA, sin(radians));
	rotMat.setElem(throughPlaneAxisB, throughPlaneAxisB, cos(radians));

	M = rotMat * M;
}
void rotate(const double degrees, Axis aboutAxis, Matrix& M)	// 3-dimensional rotation about an axis
{
	if (M.rowCount() - 1 != 3) throw "Only 3-dimensional rotations can be described as being about an axis.";

	switch (aboutAxis) {	// converts the "about axis" to the "through plane"
	case Axis::x:
		rotate(degrees, 2, 1, M);
		break;
	case Axis::y:
		rotate(degrees, 0, 2, M);
		break;
	case Axis::z:
		rotate(degrees, 1, 0, M);
		break;
	default:
		throw "Invalid axis";
	}
}
void perspective(const Camera& cam, const double aspectRatio, Matrix& M)
{
	const double& fov{ cam.fov };			// aliases for clearer code
	const double& f{ cam.farClipDist };
	const double& n{ cam.nearClipDist };

	if (n >= f) throw "Near clipping distance must be closer than the far clipping distance.";
	if (aspectRatio <= 0) throw "Aspect ratio must be positive.";
	if (M.rowCount() - 1 != 3) throw "Perspective projections can only be performed in 3-dimensions.";

	Matrix camTransMat{ Matrix::identity(M.rowCount()) };
	translate(-cam.pos, camTransMat);

	Matrix persMat{4, { 1 / tan(fov / 2), 0, 0, 0,
						0, aspectRatio / tan(fov / 2), 0, 0,
						0, 0, f / (f - n), -(f * n) / (f - n),
						0, 0, 1, 0 }};

	M = persMat * camTransMat * M;
}