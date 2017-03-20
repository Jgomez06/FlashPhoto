#ifndef STAMPERMASK_H
#define STAMPERMASK_H

#include "CircleMask.h"

/**
 * A mask subclass responsible for stamping a pre-defined but size (proportionality) scalable smiley face mask
 */
class StamperMask: public CircleMask
{
public:
	StamperMask(int diameter);
	virtual ~StamperMask();
	void getType();

protected:
	/** 
	 * Used for the retieval of the current masked pixel's influence (filled pixel for stamper drawing or unfilled for blank space).
	 */
	float calculateInfluence(int x, int y);
};

#endif

