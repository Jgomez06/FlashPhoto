#include "FPApplicationController.h"
#include "ColorData.h"
#include "PixelBuffer.h"

#include "MaskTool.h"
#include "StampTool.h"
#include "BlurTool.h"
#include "CircleMask.h"
#include "RectangleMask.h"
#include "CircleLinearFalloffMask.h"
#include "StamperMask.h"

FPApplicationController::FPApplicationController(int* width, int* height, int* curTool, ColorData* backgroundColor, PixelBuffer* displayBuffer, bool* theUndoReady, bool* theRedoReady) : ApplicationController(width, height, curTool, backgroundColor, displayBuffer, theUndoReady, theRedoReady) 
{
	m_toolManager->addTool(new MaskTool(new CircleMask(3, 1), m_currentColor, true));
	m_toolManager->addTool(new MaskTool(new CircleMask(21), m_backgroundColor, true));
	m_toolManager->addTool(new MaskTool(new CircleLinearFalloffMask(41), m_currentColor));
	m_toolManager->addTool(new MaskTool(new RectangleMask(5, 15), m_currentColor, true));
	m_toolManager->addTool(new MaskTool(new RectangleMask(5, 15, 0.3), m_currentColor, true));
	m_toolManager->addTool(new MaskTool(new StamperMask(41), m_currentColor));
	m_toolManager->addTool(new StampTool());	
	m_toolManager->addTool(new BlurTool());
}

FPApplicationController::~FPApplicationController()
{
}
