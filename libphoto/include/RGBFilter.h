#ifndef RGBFILTER_H
#define RGBFILTER_H

#include "NormalFilter.h"
#include "ColorData.h"

/**
 * Filter for scaling the RGB components of a color
 */
class RGBFilter : public NormalFilter {
public:
	RGBFilter(float rScalar, float gScalar, float bScalar);
	virtual ~RGBFilter();

protected:
	ColorData convertPixel(ColorData pixel);

private:

	float m_redScalar;
	float m_greenScalar;
	float m_blueScalar;
};

#endif

