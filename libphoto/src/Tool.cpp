#include "Tool.h"
#include "ColorData.h"
#include "PixelBuffer.h"

Tool::Tool(ColorData* currentColor, bool requiresInterpolation) {
	m_currentColor = currentColor;
	m_requiresInterpolation = requiresInterpolation;
}

Tool::Tool(ColorData* currentColor) {
	m_currentColor = currentColor;
	m_requiresInterpolation = false;
}

Tool::~Tool() {
	  delete m_currentColor;
}

void Tool::setColor(ColorData* currentColor) {
        m_currentColor = currentColor;
}

bool Tool::requiresInterpolation() const {
	return m_requiresInterpolation;
}

