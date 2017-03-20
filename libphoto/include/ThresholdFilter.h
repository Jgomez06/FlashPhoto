#ifndef THRESHOLDFILTER_H
#define THRESHOLDFILTER_H

#include "NormalFilter.h"
#include "ColorData.h"

/**
 * Filter that sets a color to one of a small set of colors based on if it meets a certain threshold
 */
class ThresholdFilter : public NormalFilter {
public:
	ThresholdFilter(float treshold);
	virtual ~ThresholdFilter();

protected:
	ColorData convertPixel(ColorData pixel);

private:

	float m_threshold;
};

#endif

