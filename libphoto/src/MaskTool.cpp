#include <math.h>
#include "MaskTool.h"
#include "Mask.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "MouseAction.h"

MaskTool::MaskTool(Mask* mask, ColorData* currentColor): Tool(currentColor) {
	setMask(mask);
}

MaskTool::MaskTool(Mask* mask, ColorData* currentColor, bool requiresInterpolation): Tool(currentColor, requiresInterpolation) {
	setMask(mask);
}

MaskTool::~MaskTool() {
	delete m_mask;
}

void MaskTool::setMask(Mask* mask) {
	m_mask = mask;
	m_mask->populate();
}

void MaskTool::onMouseAction(int x, int y, MouseAction action, PixelBuffer* buffer) {
	float new_red;
	float new_blue;
	float new_green;
	float influence;
	ColorData currentPixel;
	int offset;
	
	// offset based on mask dimensions
	offset = floor(m_mask->getWidth()/2) * -1;

	for(int row = 0; row < m_mask->getWidth(); row++){
		for(int col = 0; col < m_mask->getHeight(); col++) {
			// Get the influence at this location
			influence = m_mask->getInfluence(row,col);

			// Calculate the PixelBuffer's coordinates that correspond to the current mask coordinates
			int row_offset = x+(row+offset); 
			int col_offset = y+(col+offset);

			// Get the corresponding pixel that will updated
			currentPixel = buffer->getPixel(row_offset, col_offset);

			// Calculate the new color values 
			new_red   = influence * m_currentColor->getRed()   + ( (1-influence) * currentPixel.getRed()  );
			new_blue  = influence * m_currentColor->getBlue()  + ( (1-influence) * currentPixel.getBlue() );
			new_green = influence * m_currentColor->getGreen() + ( (1-influence) * currentPixel.getGreen());

			// Update the Pixel's color values
			currentPixel.setRed(new_red);
			currentPixel.setGreen(new_green);
			currentPixel.setBlue(new_blue);

			buffer->setPixel(row_offset, col_offset, currentPixel);
		}
	}
}

