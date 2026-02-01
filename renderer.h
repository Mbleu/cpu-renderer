#pragma once
#include "scene.h"
#include "tgaimage.h"
#include "fragment.h"
#include "rasterizer.h"
#include <vector>

constexpr int imageWidth{ 1920 };
constexpr int imageHeight{ 1080 };

class Renderer {
public:
	Renderer(const Scene& scene);
	void renderScene();

private:
	const Scene& scene;
	TGAImage image;

	void renderMesh(const Mesh& mesh);
	void renderFace(const Face& face, const std::vector<Vecd>& verts);
	void renderTri(const Tri& tri, const std::vector<Vecd>& verts);
};