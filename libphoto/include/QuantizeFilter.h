#ifndef QUANTIZEFILTER_H
#define QUANTIZEFILTER_H

#include "NormalFilter.h"
#include "ColorData.h"

/**
 * Filter for quantizing colors into a certain amount of color "bins"
 */
class QuantizeFilter : public NormalFilter {
public:
	QuantizeFilter(int bins);
	virtual ~QuantizeFilter();

protected:
	ColorData convertPixel(ColorData pixel);

private:
	int m_bins;
};

#endif

