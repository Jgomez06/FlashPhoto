#ifndef CONVOLUTIONFILTER_H
#define CONVOLUTIONFILTER_H

#include "Filter.h"
#include "PixelBuffer.h"

/**
 * Filter for convolution-based calculation
 */
class ConvolutionFilter: public Filter {
public:
	ConvolutionFilter();
	virtual ~ConvolutionFilter();

	ColorData calculate(int x, int y, PixelBuffer* buffer);
private:
	PixelBuffer* m_currentCanvas;
	
protected:
	int m_kernelSize;
	float* m_kernel;
	float m_factor;
	float m_bias;
};

#endif

