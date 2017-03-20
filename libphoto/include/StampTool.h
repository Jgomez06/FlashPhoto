#ifndef STAMPTOOL_H
#define STAMPTOOL_H

#include "Tool.h"
#include "MouseAction.h"
#include "PixelBuffer.h"
#include "Image.h"

/**
 * Tool that draws an image around the cursor when clicked
 */
class StampTool : public Tool {
public:
	StampTool();
	virtual ~StampTool();

	/**
	 * Sets the Image to be drawn with this tool.
	 */
	void setImage(Image image);
        void onMouseAction(int x, int y, MouseAction action, PixelBuffer* buffer);

private:
	Image m_image;
};

#endif

