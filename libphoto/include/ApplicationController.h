#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include "ToolManager.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include "Filter.h"
#include "CanvasManager.h"
#include "Image.h"
#include "ImageAdaptor.h"
#include <map>
#include <string>

/**
 * ApplicationController is responsible for controlling all aspects of the project code. The class    *	allows separation of project code and support code and
 * provides methods that the supporting BrushWorkApp/FlashPhotoApp/etc. class can call to modify the canvas based on interactions with the UI.
 */
class ApplicationController
{
public:
	ApplicationController(int* width, int* height, int* curTool, ColorData* backgroundColor, PixelBuffer* displayBuffer, bool* undoReady, bool* redoReady);
	ApplicationController();

	virtual ~ApplicationController();
	/**
	 * Callback for when the mouse is dragged
	 */
	void mouseDragged(int x, int y);
	/**
	 * Callback for when the mouse is clicked down
	 */
	void leftMouseDown(int x, int y, float red, float green, float blue);
	/**
	 * Callback for when the mouse is released
	 */
	void leftMouseUp(int x, int y);
	/**
	 * Applies a Filter to the current PixelBuffer.
	 */
	void applyFilterToBuffer(Filter* filter);
	/**
	 * Applies a Filter to the given PixelBuffer.
	 */
	void applyFilterToBuffer(Filter* filter, PixelBuffer* buffer);

	/**
	 * Attempts to load an image from a file with the given name
	 */
	Image loadImage(const std::string& fileName);
	void loadImageToStamp(const std::string& fileName);
	
	/**
	 * Saves an image to a file with the given name
	 */
	void saveImage(const std::string& fileName, Image image);	

	/**
	 * Redos the state of the canvas. Returns true if a window size change is required, false if otherwise.
	 */
	bool redo();
	/**
	 * Undos the state of the canvas. Returns true if a window size change is required, false if otherwise.
	 */
	bool undo();
	/**
	 * Save the state of the canvas.
	 */
	void saveCanvas();
	/**
	 * Adds the given tool to the application controller so that it can be properly tracked.
	 */
	void addTool(Tool* tool);

	/**
	 * Helper method for applying a float kernel to a ColorData. This uses the color at (x, y) and the kernel data to return a modified ColorData.
	 */
	static ColorData getColorFromKernel(int x, int y, const PixelBuffer& buffer, const float* kernel, int kernelSize, float factor, float bias);
	/**
	 * Helper method for checking if a given string is a valid file name within the context of this application (supports JPEG and PNG).
	 */
	static bool isValidFileName(const std::string fileName);

protected:
	// Track pointers from support code
	int *m_width;
	int *m_height;
	int *m_curTool;
	PixelBuffer* m_displayBuffer;
	ColorData* m_currentColor;
	ColorData* m_backgroundColor;
	ToolManager* m_toolManager;

	CanvasManager* m_canvasManager;

	int m_previousX;
	int m_previousY;

	// Status of Undo / Redo Button enabling
	bool* m_undoReady;
	bool* m_redoReady;

	std::map<std::string, ImageAdaptor*> m_imageAdaptors;

	/**
	 * Set the display buffer to the given buffer, supporting buffer size change.
	 */
	bool changeBuffer(PixelBuffer* newBuffer);

private:
	ImageAdaptor* getAdaptorFromFileName(const std::string fileName);
};

#endif

