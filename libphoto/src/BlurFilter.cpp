#include <algorithm>
#include "BlurFilter.h"

BlurFilter::BlurFilter(float amount) {
	m_kernelSize = amount;
	m_kernel = new float[m_kernelSize * m_kernelSize];
	int radius = m_kernelSize / 2;
	int inverseFactor = 0;
	for (int j = 0; j < m_kernelSize; j++) {
		int jj = abs(j - radius);
		for (int i = 0; i < m_kernelSize; i++) {
			int index = i + j * m_kernelSize;
			if (i != jj) {
				m_kernel[index] = 0;
			} else {
				m_kernel[index] = 1;
				inverseFactor++;
			}
		}
	}
	/*m_kernel = new float [25] { 0, 0, 1, 0, 0,
				    0, 1, 1, 1, 0,
				    1, 1, 1, 1, 1,
				    0, 1, 1, 1, 0,
				    0, 0, 1, 0, 0 };
	m_factor = (1.0 / (13.0 - (0.5 * amount)));*/
	m_factor = 1.0 / inverseFactor;
	m_bias = 0.0;
}

BlurFilter::~BlurFilter() {	
}

