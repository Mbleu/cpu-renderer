#include "controller.h"
#include "serialize.h"
#include "transforms.h"

const std::vector<Model>* const createBlueprints(const std::string path_s)	// Creates const blueprints
{
	std::vector<Model>* const blueprints{ new std::vector<Model> };
	Serialize::loadDir("blueprints", *blueprints);	// setup model blueprints
	return blueprints;
}

Controller::Controller(Scene& scene)
	: scene{ scene }, blueprints{ createBlueprints("blueprints") }
{
	{												// setup camera
		using enum Axis;
		scene.cam.pos[z] = -500;
	}

	// create axis waymarker
	scene.models.push_back((*blueprints)[0]);
	scene.models.push_back((*blueprints)[0]);
	scene.models.push_back((*blueprints)[0]);
	scene.models.push_back((*blueprints)[1]);
	scene.models.push_back((*blueprints)[2]);
	scene.models.push_back((*blueprints)[3]);
	scene.models.push_back((*blueprints)[4]);

	Model& xArrow{ scene.models[0] };	// aliases
	Model& yArrow{ scene.models[1] };
	Model& zArrow{ scene.models[2] };
	Model& cube{ scene.models[3] };
	Model& x{ scene.models[4] };
	Model& y{ scene.models[5] };
	Model& z{ scene.models[6] };

	xArrow.color = { 255, 0, 0, 255 };
	yArrow.color = { 0, 255, 0, 255 };
	zArrow.color = { 0, 0, 255, 255 };
	cube.color = { 255, 255, 255, 255 };
	x.color = { 255, 0, 0, 255 };
	y.color = { 0, 255, 0, 255 };
	z.color = { 0, 0, 255, 255 };

	Matrix M{ Matrix::identity(4) };
	translate(-cube.mesh.centroid(), M);
	scale(20, M);
	cube.mesh.transform(M);

	M = Matrix::identity(4);
	rotate(90, Axis::z, M);
	scale(10, M);
	translate(10, Axis::x, M);
	xArrow.mesh.transform(M);

	M = Matrix::identity(4);
	scale(10, M);
	translate(10, Axis::y, M);
	yArrow.mesh.transform(M);

	M = Matrix::identity(4);
	rotate(90, Axis::x, M);
	scale(10, M);
	translate(10, Axis::z, M);
	zArrow.mesh.transform(M);

	M = Matrix::identity(4);
	translate(-3, Axis::y, M);
	scale(10, M);
	translate(135, Axis::x, M);
	x.mesh.transform(M);

	M = Matrix::identity(4);
	translate(-3, Axis::x, M);
	scale(10, M);
	translate(135, Axis::y, M);
	y.mesh.transform(M);

	M = Matrix::identity(4);
	translate({ { -3, -3, 0 } }, M);
	scale(10, M);
	translate(135, Axis::z, M);
	z.mesh.transform(M);
}