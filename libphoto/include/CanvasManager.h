#ifndef CANVASMANAGER_H
#define CANVASMANAGER_H

#include <stack>
#include "PixelBuffer.h"

/**
 *  A configurer, user, and modifier of all PixelBuffer instances in the painting program.
 */
class CanvasManager {
public:

 	/**
	 * CanvasManager receives access to the current canvas state and saves the initial canvas.
	 */
	CanvasManager(PixelBuffer* currentCanvas, bool* theUndoReady, bool* theRedoReady);
 	/**
	 * Destroys memory allocated for member variables at program termination.
	 */
	virtual ~CanvasManager();
	/**
	 * Pushes a PixelBuffer pointer to the undo holding stack; de-activate the redo functionality.
	 */
	void saveCanvas();
	/**
	 * Pushes a previous PixelBuffer pointer to the redo holding stack and restores the canvas to its previous state by returning the stored PixelBuffer to ApplicationController.
	 */
	PixelBuffer* undo();
	/**
	 * Pushes a previous PixelBuffer pointer to the undo holding stack from the redo holding stack.
	 */
	PixelBuffer* redo();
private:
	/**
	 * Empties the redo holding stack after a new save has been chosen.
	 */
	void clearRedoStack();
	/**
	 * Updates the Undo/Redo Button readiness.
	 */
	void updateUndoRedo();
	std::stack<PixelBuffer*> undoStack;
	std::stack<PixelBuffer*> redoStack;
	PixelBuffer* m_currentCanvas;
	// Pointers to the Undo / Redo Button Status
	bool* m_undoReady;
	bool* m_redoReady;
};

#endif

