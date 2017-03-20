#include "ConvolutionFilter.h"
#include "PixelBuffer.h"
#include "ApplicationController.h"

ConvolutionFilter::ConvolutionFilter() {
}

ConvolutionFilter::~ConvolutionFilter() {
	delete [] m_kernel;
}

/**
 * Applies the "matrix" kernel to neighborhood of pixels based on given coordinates.
*/
ColorData ConvolutionFilter::calculate(int x, int y, PixelBuffer* buffer) {
	return ApplicationController::getColorFromKernel(x, y, *buffer, m_kernel, m_kernelSize, m_factor, m_bias);
}

