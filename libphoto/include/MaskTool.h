#ifndef MASKTOOL_H
#define MASKTOOL_H

#include "Tool.h"
#include "Mask.h"
#include "MouseAction.h"
#include "PixelBuffer.h"

/**
 * A Tool that draws to the canvas based on its associated Mask
 */
class MaskTool : public Tool {
public:
	MaskTool(Mask* mask, ColorData* currentColor);
	MaskTool(Mask* mask, ColorData* currentColor, bool requiresInterpolation);
	virtual ~MaskTool();

	/**
	 * Sets the mask for this MaskTool to use when being drawn to the PixelBuffer.
	 */
	void setMask(Mask* mask);
        void onMouseAction(int x, int y, MouseAction action, PixelBuffer* buffer);

private:
	Mask* m_mask;
};

#endif

