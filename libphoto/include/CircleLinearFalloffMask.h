#ifndef CIRCLELINEARFALLOFFMASK_H
#define CIRCLELINEARFALLOFFMASK_H

#include "CircleMask.h"

/**
 * Circle mask with linear falloff behavior
 */
class CircleLinearFalloffMask: public CircleMask {
public:
	CircleLinearFalloffMask(int radius);
	virtual ~CircleLinearFalloffMask();

protected:
	float calculateInfluence(int x, int y);
};

#endif

