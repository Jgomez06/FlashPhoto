#ifndef BLURTOOL_H
#define BLURTOOL_H

#include "Tool.h"
#include "MouseAction.h"
#include "PixelBuffer.h"

/**
 * Tool that blurs pixels in a circular shape around the cursor
 */
class BlurTool : public Tool {
public:
	BlurTool();
	virtual ~BlurTool();

        void onMouseAction(int x, int y, MouseAction action, PixelBuffer* buffer);

private:
	float* m_blurKernel;
};

#endif

