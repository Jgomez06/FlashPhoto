#include "EdgeDetectFilter.h"
#include "PixelBuffer.h"
#include "ColorData.h"

EdgeDetectFilter::EdgeDetectFilter() {
	m_kernelSize = 5;
	m_kernel = new float [25] { 0, 0, -1, 0, 0,
				    0, 0, -1, 0, 0,
				    0, 0,  2, 0, 0,
				    0, 0, 0, 0, 0,
				    0, 0, 0, 0, 0 };
	m_factor = 1.0;
	m_bias = 0.0;
}

EdgeDetectFilter::~EdgeDetectFilter() {	
}

