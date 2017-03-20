#include "CircleLinearFalloffMask.h"

CircleLinearFalloffMask::CircleLinearFalloffMask(int diameter): CircleMask(diameter, NO_BASE_INFLUENCE)
{
}

CircleLinearFalloffMask::~CircleLinearFalloffMask()
{
}

float CircleLinearFalloffMask::calculateInfluence(int x, int y)
{
	int radius = m_diameter / 2;
	int centerX = radius;
	int centerY = radius;
	int xx = x - centerX;
	int yy = y - centerY;
	int distanceSquared = xx * xx + yy * yy;
	int radiusSquared = radius * radius;
    // Same logic as CircleMask, but return less influential values as the point becomes further from center
	if (distanceSquared <= radiusSquared) {
		return 0.8f * (1.0f - ((float) distanceSquared / (float) radiusSquared));
	}
	return 0;
}
