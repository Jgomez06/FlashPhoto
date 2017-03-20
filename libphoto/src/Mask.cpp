#include "Mask.h"
#include <iostream>

Mask::Mask(int width, int height, float baseInfluence): m_width(width), m_height(height), m_baseInfluence(baseInfluence)
{
	m_influence = new float[width * height];
}

Mask::Mask(int width, int height): m_width(width), m_height(height), m_baseInfluence(DEFAULT_INFLUENCE)
{
	m_influence = new float[width * height];
}

Mask::~Mask()
{
	delete [] m_influence;
}


float Mask::getInfluence(int x, int y)
{
	int index = x + y * m_width;
	if (index < 0 || index >= m_width * m_height) {
		// Illegal index, throw exception here
	}
	
	return m_influence[index];
}

void Mask::populate()
{
    // Call subclass implementation of calculateInfluence for each (x,y) mask coordinate
	for (int x = 0; x < m_width; x++) {
		for (int y = 0; y < m_height; y++) {
			m_influence[x + y * m_width] = calculateInfluence(x, y);
		}
	}
}

const int Mask::getWidth()
{
  return m_width;
}

const int Mask::getHeight()
{
  return m_height;
}
