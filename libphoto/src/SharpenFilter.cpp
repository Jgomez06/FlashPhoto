#include "SharpenFilter.h"
#include "PixelBuffer.h"
#include "ColorData.h"

SharpenFilter::SharpenFilter(float amount) {
	m_kernelSize = 5;
	m_kernel = new float [25] { -1, -1, -1, -1, -1,
				    -1,  2,  2,  2, -1,
				    -1,  2,  8,  2, -1,
				    -1,  2,  2,  2, -1,
				    -1, -1, -1, -1, -1 };
	m_factor = 1.0 / (8.0 - (0.75 * amount));
	m_bias = 0.0;
}

SharpenFilter::~SharpenFilter() {	
}

