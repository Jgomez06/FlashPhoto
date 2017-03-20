#ifndef SHARPENFILTER_H
#define SHARPENFILTER_H

#include "ConvolutionFilter.h"

/**
 * Convolution-based filter where the canvas is sharpened a certain amount
 */
class SharpenFilter: public ConvolutionFilter {
public:
	SharpenFilter(float amount);
	virtual ~SharpenFilter();
};

#endif

