#pragma once
#include "tgaimage.h"
#include <vector>

const TGAColor red{ 255, 0, 0, 255 };
const TGAColor green{ 0, 255, 0, 255 };
const TGAColor blue{ 0, 0, 255, 255 };
const TGAColor yellow{ 255, 255, 0, 255 };
const TGAColor cyan{ 0, 255, 255, 255 };
const TGAColor magenta{ 255, 0, 255, 255 };
const TGAColor white{ 255, 255, 255, 255 };
const TGAColor black{ 0, 0, 0, 255 };

const std::vector<const TGAColor*> colors{ &red, &green, &blue, &yellow, &cyan, &magenta };

struct Fragment {
	double xPos;
	double yPos;
	double depth;
	TGAColor color;
};

class FragmentManager {
public:
	FragmentManager(const int width, const int height);
	Fragment& getFrag(const int x, const int y);

private:
	int width;
	std::vector<Fragment> fragments;
};