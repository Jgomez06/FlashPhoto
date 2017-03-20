#include <cstddef>
#include "BlurTool.h"
#include "MouseAction.h"
#include "PixelBuffer.h"
#include "ApplicationController.h"
#include <iostream>

BlurTool::BlurTool(): Tool(NULL) {
	m_blurKernel = new float[9] { 0.0, 0.3, 0.0,
				      0.05, 0.3, 0.05,
				      0.0, 0.3, 0.0 };
}

BlurTool::~BlurTool() {
	delete [] m_blurKernel;
}

void BlurTool::onMouseAction(int x, int y, MouseAction action, PixelBuffer* buffer) {
	//std::cout << "BlueAction " << std::endl;
	int diameter = 41;
	int radius = diameter / 2;
	int bufferWidth = buffer->getWidth();
	int bufferHeight = buffer->getHeight();
	// Set points within a circle of radius m_blurSize to new colors based on blur parameters
	for (int i = 0; i < diameter; i++) {
		for (int j = 0; j < diameter; j++) {
			int xPos = x - radius + i;
			int yPos = y - radius + j;
			if (xPos < 0 || xPos >= bufferWidth || yPos < 0 || yPos >= bufferHeight) {
				continue;
			}
			int ii = i - radius;
			int jj = j - radius;
			if ((ii * ii) + (jj * jj) <= radius * radius) {
				ColorData color = ApplicationController::getColorFromKernel(xPos, yPos, *buffer, m_blurKernel, 3, 1.0, 0.0);
				buffer->setPixel(xPos, yPos, color);
			}
		}
	}
}

