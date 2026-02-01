#include "renderer.h"

bool isBackFace(const Face& face);

Renderer::Renderer(const Scene& scene)
	: scene{ scene }, image{ imageWidth, imageHeight, TGAImage::RGB }
{}

void Renderer::renderScene()
{
	for (const Model& model : scene.models)
	{
		//if (!inViewFrustrum(model.mesh)) continue;

		renderMesh(model.mesh);
	}
}

void Renderer::renderMesh(const Mesh& mesh)
{
	Mesh projection{ mesh };

	for (const Face& face : projection.getFaces())
	{
		if (isBackFace(face)) continue;

		renderFace(face, mesh.getVerts());
	}
}

void Renderer::renderFace(const Face& face, const std::vector<Vecd>& verts)
{
	for (const Tri& tri : face.getTris())
		renderTri(tri, verts);
}

void Renderer::renderTri(const Tri& tri, const std::vector<Vecd>& verts)
{
	//if (!inViewBox(tri, verts)) return;	// skip rendering if tri is outside of the 3d view box
	//if (isDegen(tri, verts)) return;	// skip rendering if degenerate
	std::vector<Fragment> triFrags;

	// rasterize into fragments (create the fragments)
	rasterTri(tri, verts, imageWidth, imageHeight, triFrags);
	
	// shade fragments
	// check subpixel coverage lines
	// depth test
	// blend
	// write all fragments to frame
	// display frame
}

void Renderer::renderScene()
{
	for (const Model& model : scene.models) {
		// frustrum clipping continue;

		// project to screen coords
		Mesh projection{ model.mesh };

		for (const Face& face : projection.getFaces()) {
			// backface culling continue;

			for (const Tri& tri : face.getTris()) {
				// rasterize into fragments
				// shade fragments (interpolate color etc.)
				// 
			}
		}
			
	}


	for (int y{ 0 }; y < fragments.size(); ++y)				// reset depth buffer
		for (int x{ 0 }; x < fragments[0].size(); ++x)
			fragments[y][x].depth = scene.cam.farClipDist;

	const double aspectRatio{ double(fragments[0].size()) / double(fragments.size()) };

	for (const Model& model : scene.models) {
		//if (frustrumCull(scene.cam, aspectRatio, model)) continue;

		Mesh projection{ model.mesh };

		projection.transform(
			projection.scale({ {double(fragments[0].size()) / 2., double(fragments.size()) / 2., 1.} })		// denormalise the projection by scaling to the image size
			* projection.translate({ {1, 1, 0} })															// translate normalised projection into the positive plane quadrant
			* projection.perspective(scene.cam, aspectRatio));												// perform a perspective transform

		for (const Face& face : projection.getFaces()) {
			if (isBackFace(face)) continue;					// cull back faces

			for (const Tri& tri : face.getTris()) {
				if (model.showFaces) 
					rasterizer.rasterTri(tri, model.color);	// raster faces

				if (model.showEdges)
					for (int i{ 0 }; i < tri.verts.size(); ++i)
						rasterizer.rasterEdge(*tri.verts[i], *tri.verts[(i + 1) % tri.verts.size()]);	// raster edges (wire-frame)
			}
		}
	}

	for (int y{ 0 }; y < fragments.size(); ++y)			// color pixels using fragment data
		for (int x{ 0 }; x < fragments[0].size(); ++x)
			image.set(x, y, fragments[y][x].color);

	image.flip_vertically(); // all calculations use origin bot-left but TGA images use top-left so we have to flip
	image.write_tga_file("output.tga");
}

bool isBackFace(const Face& face)
{
	Vecd AB{ *face.getVerts()[1] - *face.getVerts()[0] };
	Vecd AC{ *face.getVerts()[2] - *face.getVerts()[0] };
	Vecd normal{ xprod(AB, AC) };

	if (normal[2] < 0) return true;	// if the z-component of the normal is negative then the face is facing backwards
	else return false;
}