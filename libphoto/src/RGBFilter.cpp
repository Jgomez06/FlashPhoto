#include "RGBFilter.h"
#include "ColorData.h"

RGBFilter::RGBFilter(float rScalar, float gScalar, float bScalar): m_redScalar(rScalar), m_greenScalar(gScalar), m_blueScalar(bScalar)
{
}

RGBFilter::~RGBFilter()
{
}

ColorData RGBFilter::convertPixel(ColorData pixel){

	float newRed, newBlue, newGreen;

	newRed   = pixel.getRed()   * m_redScalar;
	newGreen = pixel.getGreen() * m_greenScalar;
	newBlue  = pixel.getBlue()  * m_blueScalar; 

	return ColorData(newRed, newGreen, newBlue);
}
