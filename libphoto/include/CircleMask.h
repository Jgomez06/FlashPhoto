#ifndef CIRCLEMASK_H
#define CIRCLEMASK_H

#include "Mask.h"

/**
 * Mask for a circle shape
 */
class CircleMask: public Mask {
public:
	CircleMask(int diameter, float baseInfluence);
	CircleMask(int diameter);
	virtual ~CircleMask();

protected:
	int m_diameter;
	virtual float calculateInfluence(int x, int y);
};

#endif

