//
//  CanvasManager.cpp
//  Author: Peter Fomin 3/31/2016
//
//  A configurer, user, and modifier of all PixelBuffer instances in the FlashPhoto program.
//

#include <cstring>
#include <stdlib.h>
#include "CanvasManager.h"
#include "PixelBuffer.h"
#include <stack>
#include "ColorData.h"

using std::fill;
using std::stack;

// CanvasManager receives access to the current canvas state and saves the initial canvas.
CanvasManager::CanvasManager(PixelBuffer* currentCanvas, bool* theUndoReady, bool* theRedoReady)
{
    m_undoReady = theUndoReady;
    m_redoReady = theRedoReady;
    m_currentCanvas = currentCanvas;
    saveCanvas();
}
// Destroys memory allocated for member variables at program termination.
CanvasManager::~CanvasManager() 
{
    delete m_undoReady;
    delete m_redoReady;
    delete m_currentCanvas;
}
/**
 * Pushes a PixelBuffer pointer to the undo holding stack; de-activate the redo functionality.
*/
void CanvasManager::saveCanvas() 
{
    PixelBuffer* aSavePixelBuffer = new PixelBuffer(m_currentCanvas->getWidth(), m_currentCanvas->getHeight(), new ColorData(0,0,0));
    PixelBuffer::copyPixelBuffer(m_currentCanvas, aSavePixelBuffer);
    undoStack.push(aSavePixelBuffer);
    clearRedoStack();
    updateUndoRedo();
} 
/**
 * Pushes a previous PixelBuffer pointer to the redo holding stack and restores the canvas to its previous state by returning the stored PixelBuffer to ApplicationController.
*/
PixelBuffer* CanvasManager::undo() {
	PixelBuffer* buffer = NULL;
	if (undoStack.size() > 1) {
		redoStack.push(undoStack.top());
		undoStack.pop();
		buffer = undoStack.top();
	}
	updateUndoRedo();
	return buffer;
}

/**
 * Pushes a previous PixelBuffer pointer to the undo holding stack from the redo holding stack.
*/
PixelBuffer* CanvasManager::redo() {
	PixelBuffer* buffer = NULL;
	if (!redoStack.empty())
	{
		undoStack.push(redoStack.top());
		redoStack.pop();
		buffer = undoStack.top();
	}
	updateUndoRedo();
	return buffer;
}

/**
 * Empties the redo holding stack after a new save has been chosen.
*/
void CanvasManager::clearRedoStack()
{
	while (!redoStack.empty())
	{
		redoStack.pop();
	}
}

/**
 * Updates the Undo/Redo Button readiness.
*/
void CanvasManager::updateUndoRedo()
{
    if(undoStack.size() > 1)
    {
        *m_undoReady = true;
    } else {
        *m_undoReady = false;
    }
    if(redoStack.size() > 0)
    {
        *m_redoReady = true;
    } else {
        *m_redoReady = false;
    }
}


