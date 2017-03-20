//
//  StamperMask.cpp
//  Author: Peter Fomin 2/28/2016
//
//  A mask subclass responsible for stamping a pre-defined but size (proportionality) scalable smiley face fask.
//

#include "StamperMask.h"
#include <iostream>

StamperMask::StamperMask(int radius): CircleMask(radius, NO_BASE_INFLUENCE)
{
}

StamperMask::~StamperMask()
{
}
// Used for the retieval of the current masked pixel's influence (filled pixel for stamper drawing or unfilled for blank space).
float StamperMask::calculateInfluence(int x, int y)
{
    // Distances used to interpret mask array locations
		int radius = m_diameter / 2;
		int centerX = radius;
		int centerY = radius;
		int xx = x - centerX;
		int yy = y - centerY;
		int distanceSquared = xx * xx + yy * yy;
		int radiusSquared = radius * radius;
		
		// define bounds range for drawing enclosing circle
		if ((distanceSquared <= radiusSquared) && (distanceSquared >= (radiusSquared*0.9))) {
			return 1.0;
		}
		// define bounds range for drawing semi-circle smile
		if ((distanceSquared <= (radiusSquared * 0.60)) && (distanceSquared >=  (radiusSquared*0.55))) {
			if (yy < 0) {
				return 1.0;
			}
		}
		// define bounds range for drawing right eye rectangle
		if ((xx > (radius *0.20)) && (xx < (radius *0.30)) && (yy > 0) && (distanceSquared < (radiusSquared * 0.75))) {
			return 1.0;
		}
		// define bounds range for drawing left eye rectangle
		if ((x > (radius *0.7)) && (x < (radius *0.80)) && (yy > 0) && (distanceSquared < (radiusSquared * 0.75))) {
			return 1.0;
		}
		return 0;
}
