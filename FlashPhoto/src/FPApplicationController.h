#ifndef FPAPPLICATIONCONTROLLER_H
#define FPAPPLICATIONCONTROLLER_H

#include "ApplicationController.h"
#include "PixelBuffer.h"
#include "ColorData.h"

/**
 * ApplicationController for FlashPhoto
 */
class FPApplicationController : public ApplicationController 
{
public:
	FPApplicationController(int* width, int* height, int* curTool, ColorData* backgroundColor, PixelBuffer* displayBuffer, bool* undoReady, bool* redoReady);
	virtual ~FPApplicationController();
};
#endif

