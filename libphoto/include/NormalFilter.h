#ifndef NORMALFILTER_H
#define NORMALFILTER_H

#include "Filter.h"
#include "ColorData.h"
#include "PixelBuffer.h"

/**
 * Represents a "normal" filter that simply calculates from pixel to pixel
 */
class NormalFilter : public Filter {
protected:	
	ColorData calculate(int x, int y, PixelBuffer* buffer);
	/**
 	 * Converts the current pixel on the canvas to some new ColorData value based on an algorithm implementation.
 	 */
	virtual ColorData convertPixel(ColorData pixel) = 0;
};

#endif

