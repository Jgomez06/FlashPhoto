#ifndef TOOLMANAGER_H
#define TOOLMANAGER_H

#include "Tool.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "MouseAction.h"
#include "Image.h"
#include "StampTool.h"
#include <vector>
#include <string>
#include <sstream>
/**
 *  A configurer, user, and modifier of all tool instances in the BrushWork program.
 */
class ToolManager {
public:
	ToolManager(ColorData* currentColor, int* currentTool, ColorData* backgroundColor);
	virtual ~ToolManager();
 
	/**
	 * Calls the current tool's draw method
	 */	
	void useCurrentTool(int x, int y, MouseAction action, PixelBuffer* buffer, int previousX, int previousY);
	/**
	 * Sets the image to be used for the stamp tool
	 */	
	void setStampImage(Image image);
	/**
	 * Adds the given Tool to the ToolManager
	 */
	void addTool(Tool* t);
	
private:

	int toolCount;
	// Array of available tools
	std::vector<Tool*> m_tools;

	// Pointer to the single selected tool
	int* m_currentTool;
 
  	// Pointer to the selected color
  	ColorData* m_currentColor;
  
  	// Pointer to the current background color
  	ColorData* m_backgroundColor;

	StampTool* m_stampTool;

	void drawLine(int x1, int y1, int x2, int y2, MouseAction action, PixelBuffer* buffer, int width, int height);

    	// Used in file operations for testing
    	int m_fp;
	
	void writeToFile(char action, int x, int y);
};

#endif

