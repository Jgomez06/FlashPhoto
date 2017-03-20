#ifndef SATURATIONFILTER_H
#define SATURATIONFILTER_H

#include "NormalFilter.h"
#include "ColorData.h"

/**
 * Filter for saturating colors a certain amount
 */
class SaturationFilter : public NormalFilter {
public:
	SaturationFilter(float threshold);
	virtual ~SaturationFilter();

protected:
	ColorData convertPixel(ColorData pixel);

private:

	float m_saturation;
};

#endif

