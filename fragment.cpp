#include "fragment.h"

FragmentManager::FragmentManager(const int width, const int height)
	: width(width), fragments(width * height)
{}
Fragment& FragmentManager::getFrag(const int x, const int y)
{
	return fragments[x + y * width];
}