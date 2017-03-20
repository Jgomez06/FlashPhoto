#ifndef TOOL_H
#define TOOL_H

#include "ColorData.h"
#include "PixelBuffer.h"
#include "MouseAction.h"

/**
 * Represents a drawing tool. A tool has some canvas modification behavior depending on its type.
 */
class Tool {
public:
	Tool(ColorData* currentColor);
	Tool(ColorData* currentColor, bool requiresInterpolation);
	virtual ~Tool();

	/**
	 * Sets the ColorData pointer for this Tool to use when drawing.
	 */
	void setColor(ColorData* currentColor);
	/**
	 * Callback for when a mouse action occurs (CLICK, DRAG, etc.). This is where Tool subclasses should modify the PixelBuffer.
	 */
        virtual void onMouseAction(int x, int y, MouseAction action, PixelBuffer* buffer) = 0;
	/**
	 * Returns whether this Tool requires linear interpolation whilst being drawn. Defaults to false.
	 */
	bool requiresInterpolation() const;

protected:
	ColorData* m_currentColor;

private:
	bool m_requiresInterpolation;
};

#endif

