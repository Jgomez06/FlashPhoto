#ifndef SEPIATONEFILTER_H
#define SEPIATONEFILTER_H

#include "NormalFilter.h"
#include "ColorData.h"

/**
 * Filters all pixels to be sepia-toned
 */
class SepiaToneFilter : public NormalFilter {
public:
	SepiaToneFilter();
	virtual ~SepiaToneFilter();

protected:
	ColorData convertPixel(ColorData pixel);
};

#endif

