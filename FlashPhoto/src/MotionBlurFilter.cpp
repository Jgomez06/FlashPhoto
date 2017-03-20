#include "MotionBlurFilter.h"

MotionBlurFilter::MotionBlurFilter(float amount, int direction) {
	// Dynamically create kernel based on given amount and direction
	m_kernelSize = amount;
	m_kernel = new float[m_kernelSize * m_kernelSize];
	for (int i = 0 ; i < m_kernelSize; i++) {
		for (int j = 0; j < m_kernelSize; j++) {
			int index = i + j * m_kernelSize;
			if (direction == 0) {
				// North/South
				m_kernel[index] = i == m_kernelSize / 2 ? 1 : 0;		
			} else if (direction == 1) {
				// East/West
				m_kernel[index] = j == m_kernelSize / 2 ? 1 : 0;
			} else if (direction == 2) {
				// Northeast/Southwest
				m_kernel[index] = i == j ? 1 : 0;
			} else if (direction == 3) {
				// Northwest/Southeast
				m_kernel[index] = i == m_kernelSize - j - 1 ? 1 : 0;
			}
		}
	}
	m_factor = 1.0 / m_kernelSize;
	m_bias = 0.0;
}

MotionBlurFilter::~MotionBlurFilter() {	
}

