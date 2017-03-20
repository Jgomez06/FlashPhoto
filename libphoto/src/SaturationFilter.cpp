#include "SaturationFilter.h"
#include "ColorData.h"

SaturationFilter::SaturationFilter(float saturation): m_saturation(saturation)
{
}

SaturationFilter::~SaturationFilter()
{
}

ColorData SaturationFilter::convertPixel(ColorData pixel)
{
	float greyScale;
	float newRed, newBlue, newGreen;

	greyScale = pixel.getLuminance();

	newRed   = m_saturation * pixel.getRed()  +  (1 - m_saturation) * greyScale;
	newBlue  = m_saturation * pixel.getBlue() +  (1 - m_saturation) * greyScale;
	newGreen = m_saturation * pixel.getBlue() +  (1 - m_saturation) * greyScale;

	return ColorData(newRed, newGreen, newBlue);
}
