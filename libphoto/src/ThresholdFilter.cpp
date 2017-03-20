#include "ThresholdFilter.h"
#include "ColorData.h"

ThresholdFilter::ThresholdFilter(float threshold): m_threshold(threshold)
{
}

ThresholdFilter::~ThresholdFilter()
{
}

ColorData ThresholdFilter::convertPixel(ColorData pixel)
{
	float newRed, newBlue, newGreen;

	if(pixel.getRed() > m_threshold)
		newRed = 1.0;
	else
		newRed = 0.0;

	if(pixel.getBlue() > m_threshold)
		newBlue = 1.0;
	else
		newBlue = 0.0;

	if(pixel.getGreen() > m_threshold)
		newGreen = 1.0;
	else
		newGreen = 0.0;

	return ColorData(newRed, newGreen, newBlue);
}
