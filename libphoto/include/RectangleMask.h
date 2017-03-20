#ifndef RECTANGLEMASK_H
#define RECTANGLEMASK_H

#include "Mask.h"

/**
 * Mask with a rectangle shape
 */
class RectangleMask: public Mask {
public:
	RectangleMask(int width, int height, float baseInfluence);
	RectangleMask(int width, int height);
	virtual ~RectangleMask();

protected:
	float calculateInfluence(int x, int y);
};

#endif

