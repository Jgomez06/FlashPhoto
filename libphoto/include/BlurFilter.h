#ifndef BLURFILTER_H
#define BLURFILTER_H

#include "ConvolutionFilter.h"

/**
 * Convolution-based filter where pixels are blurred
 */
class BlurFilter: public ConvolutionFilter {
public:
	BlurFilter(float amount);
	virtual ~BlurFilter();
};

#endif

