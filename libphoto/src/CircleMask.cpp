#include "CircleMask.h"

CircleMask::CircleMask(int diameter, float baseInfluence): Mask(diameter, diameter, baseInfluence), m_diameter(diameter) {
}

CircleMask::CircleMask(int diameter): Mask(diameter, diameter), m_diameter(diameter) {
}

CircleMask::~CircleMask() {
}

float CircleMask::calculateInfluence(int x, int y) {
	int radius = m_diameter / 2;
	int xx = x - radius;
	int yy = y - radius;
	if ((xx * xx) + (yy * yy) <= radius * radius) {
		// Point is within the circle, give it an influence
		return m_baseInfluence;
	}
	return 0; // Point is not within the circle so it should have zero influence
}

