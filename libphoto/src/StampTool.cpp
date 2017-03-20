#include <cstddef>
#include "StampTool.h"
#include "MouseAction.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include "Image.h"
#include "Tool.h"
#include <iostream>

StampTool::StampTool(): Tool(NULL) {
}

StampTool::~StampTool() {
}

void StampTool::setImage(Image image) {
	m_image = image;
}

void StampTool::onMouseAction(int x, int y, MouseAction action, PixelBuffer* buffer) {
	if (action == CLICK) {
		m_image.applyToBuffer(buffer, x - m_image.getWidth() / 2, y - m_image.getHeight() / 2); 
	}
}

