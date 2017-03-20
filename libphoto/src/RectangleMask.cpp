#include "RectangleMask.h"
#include <iostream>

RectangleMask::RectangleMask(int width, int height, float baseInfluence): Mask(width, height, baseInfluence)
{
}

RectangleMask::RectangleMask(int width, int height): Mask(width, height)
{
}

RectangleMask::~RectangleMask()
{
}

float RectangleMask::calculateInfluence(int x, int y)
{

	return m_baseInfluence;
}
