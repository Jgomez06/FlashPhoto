#ifndef MOTIONBLURFILTER_H
#define MOTIONBLURFILTER_H

#include "ConvolutionFilter.h"

/**
 * Convolution-based filter where pixels are blurred in a certain direction
 */
class MotionBlurFilter: public ConvolutionFilter {
public:
	MotionBlurFilter(float amount, int direction);
	virtual ~MotionBlurFilter();
};

#endif

