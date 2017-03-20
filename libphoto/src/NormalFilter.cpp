#include "NormalFilter.h"
#include "ColorData.h"
#include "PixelBuffer.h"

ColorData NormalFilter::calculate(int x, int y, PixelBuffer* buffer)
{
	return convertPixel(buffer->getPixel(x,y));	
}
