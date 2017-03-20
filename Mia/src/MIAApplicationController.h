#ifndef MIAAPPLICATIONCONTROLLER_H
#define MIAAPPLICATIONCONTROLLER_H

#include "ApplicationController.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include <stack>

/**
 * ApplicationController for Mia
 */
class MIAApplicationController : public ApplicationController 
{
public:
	MIAApplicationController(int* width, int* height, int* curTool, ColorData* backgroundColor, PixelBuffer* displayBuffer, bool* undoReady, bool* redoReady);

	virtual ~MIAApplicationController();
	/**
 	 * Cycles to the next image in the flipper stack, returning a PixelBuffer representation
 	 */
	PixelBuffer* nextImage();
	/**
 	 * Cycles to the previous image in the flipper stack, returning a PixelBuffer representation
 	 */
	PixelBuffer* previousImage();
	/**
 	 * Loads an image in the flipper directory.
 	 */
	void loadFlipperImage();
private:
	void clearStacks();
	std::stack<PixelBuffer*> previousStack;
	std::stack<PixelBuffer*> nextStack;
	PixelBuffer* m_currentCanvas;

};
#endif

