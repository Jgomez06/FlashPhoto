#ifndef FILTER_H
#define FILTER_H

#include "PixelBuffer.h"

/**
 * Represents a Filter for modification of the canvas using some algorithm
 */
class Filter {
public:
	/**
 	 * Applies this filter to the given PixelBuffer
 	 */
	void applyToBuffer(PixelBuffer* buffer);
		
protected:
	/**
 	 * Calculates a new ColorData value based on some algorithm specified by subclass implementations.
 	 */
	virtual ColorData calculate(int x, int y, PixelBuffer* buffer) = 0; 
};

#endif

