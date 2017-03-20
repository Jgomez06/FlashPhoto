#include "MIAApplicationController.h"
#include "ColorData.h"
#include "PixelBuffer.h"

#include "MaskTool.h"
#include "StampTool.h"
#include "CircleMask.h"

#include <cstring>
#include <stdlib.h>
#include <stack>

using std::fill;
using std::stack;

// A  subclass of ApplicationController Extended to include the 3D Viewing Functionality.
MIAApplicationController::MIAApplicationController(int* width, int* height, int* curTool, ColorData* backgroundColor, PixelBuffer* displayBuffer, bool* theUndoReady, bool* theRedoReady) : ApplicationController(width, height, curTool, backgroundColor, displayBuffer, theUndoReady, theRedoReady) 
{
	*m_currentColor = ColorData(1.0,0,0);
	m_toolManager->addTool(new MaskTool(new CircleMask(3, 1), m_currentColor, true));
	StampTool* stamp = new StampTool();
	Image image = loadImage("marker.png");
	stamp->setImage(image);
	m_toolManager->addTool(stamp);	
    m_currentCanvas = displayBuffer;
}

MIAApplicationController::~MIAApplicationController()
{

}
// Clears the stacks when a new directory image is reloaded.
void MIAApplicationController::clearStacks()
{
    while (!previousStack.empty())
    {
        previousStack.pop();
    }
    while (!nextStack.empty())
    {
        nextStack.pop();
    }
}
// Event Callback that handles stack setup for image in the flipper directory.
void MIAApplicationController::loadFlipperImage()
{
    clearStacks();
}
// Cycles to the next image in the flipper stack if it exists, returning a PixelBuffer representation.
PixelBuffer* MIAApplicationController::nextImage()
{
    PixelBuffer* aSavePixelBuffer = new PixelBuffer(m_currentCanvas->getWidth(), m_currentCanvas->getHeight(), new ColorData(0,0,0));
    PixelBuffer::copyPixelBuffer(m_currentCanvas, aSavePixelBuffer);
    previousStack.push(aSavePixelBuffer);
    if (!nextStack.empty())
    {
        PixelBuffer* buffer = NULL;
        buffer = nextStack.top();
        nextStack.pop();
        changeBuffer(buffer);
        return buffer;
    } else {
        return NULL;
    }
}
// Cycles to the previous image in the flipper stack if it exists, returning a PixelBuffer representation.
PixelBuffer* MIAApplicationController::previousImage()
{
    PixelBuffer* aSavePixelBuffer = new PixelBuffer(m_currentCanvas->getWidth(), m_currentCanvas->getHeight(), new ColorData(0,0,0));
    PixelBuffer::copyPixelBuffer(m_currentCanvas, aSavePixelBuffer);
    nextStack.push(aSavePixelBuffer);
    if (!previousStack.empty())
    {
        PixelBuffer* buffer = NULL;
        buffer = previousStack.top();
        previousStack.pop();
        changeBuffer(buffer);
        return buffer;
    } else {
        return NULL;
    }
}
