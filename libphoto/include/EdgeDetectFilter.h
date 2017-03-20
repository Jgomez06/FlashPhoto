#ifndef EDGEDETECTFILTER_H
#define EDGEDETECTFILTER_H

#include "ConvolutionFilter.h"

/**
 * Convolution-based filter for edge detection behavior
 */
class EdgeDetectFilter: public ConvolutionFilter {
public:
	EdgeDetectFilter();
	virtual ~EdgeDetectFilter();
};

#endif

