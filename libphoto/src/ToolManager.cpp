#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "ToolManager.h"
#include "ColorData.h"
#include "MaskTool.h"
#include "StampTool.h"
#include "CircleMask.h"
#include "RectangleMask.h"
#include "MouseAction.h"
#include "Image.h"
#include <vector>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), creat() */
#include <stdio.h>    /* For perror()*/

// Receives Current color and tool selections for proper ToolManager functions.
ToolManager::ToolManager(ColorData* currentColor, int* currentTool, ColorData* backgroundColor) {
	m_currentColor = currentColor;
	m_currentTool = currentTool;
	m_backgroundColor = backgroundColor;
	m_stampTool = new StampTool();

	// For Testing tools
	//int perms = 0740;
	//if ((m_fp = open("../tests/commands/renameME.txt", (O_WRONLY | O_CREAT), perms)) == -1) {
     	//	perror("Failed to open file:");
     	//}
}

void delete_tool_p(Tool *tool) {
	delete tool;
}

ToolManager::~ToolManager() {
	delete m_currentColor;
	delete m_backgroundColor;
	//std::for_each(m_tools.begin(), n_tools.end(), delete_tool_p<Tool>); 
	delete m_currentTool;
}

// Finds and retrieves the current Tool; calls the Tool onMouseAction method.
void ToolManager::useCurrentTool(int x, int y, MouseAction action, PixelBuffer* buffer, int previousX, int previousY) {
	std::stringstream sstm;
	int width = buffer->getWidth();
	int height = buffer->getHeight();
	if (x >= 0 && x < width && y >= 0 && y < height) {
		// If the mouse is being dragged, check if drawing requires linear interpolation
		Tool* tool = m_tools[*m_currentTool];
		if (action == DRAG) {
			if (tool->requiresInterpolation()) {
				drawLine(x, height - y, previousX, height - previousY, DRAG, buffer, width, height);
				return;
			}
		}
       		//writeToFile('c', x, height-y);
		tool->onMouseAction(x, height - y, action, buffer);	
	}
}

void ToolManager::setStampImage(Image image) {
	m_stampTool->setImage(image);
	m_tools[6] = m_stampTool;
}

/* Source: http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B */
// Produces line smoothing effect between ToolManager::useCurrentTool Applications. Algorithm used and cited from listed source.
void ToolManager::drawLine(int x2, int y2, int x1, int y1, MouseAction action, PixelBuffer* buffer, int width, int height) {
	const bool steep = (abs(y2 - y1) > abs(x2 - x1));
	if(steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}
 
	if(x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
 
	const float dx = x2 - x1;
	const float dy = abs(y2 - y1);
 
	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;
 
	const int maxX = (int)x2;
 
	for(int x=(int)x1; x<maxX; x++)
	{
		if(steep)
		{
			if (x >= 0 && x < width && y >= 0 && y < height) {
				//writeToFile('d', y, x);	
				m_tools[*m_currentTool]->onMouseAction(y,x, action, buffer);
			}
		}
		else
		{
			if (x >= 0 && x < width && y >= 0 && y < height) {
				//writeToFile('d', x, y);	
				m_tools[*m_currentTool]->onMouseAction(x,y, action, buffer);
			}
		}
 
		error -= dy;
		if(error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

void ToolManager::addTool(Tool* tool){
	
	m_tools.push_back(tool);
	
}

void ToolManager::writeToFile(char action, int x, int y) {
				
	std::stringstream sstm;
       	sstm << action << " " << x << " " << y << " " << m_currentColor->getRed() << " " << m_currentColor->getGreen() << " " << m_currentColor->getBlue() << "\n";
       	std::string cmd = sstm.str();
       	write(m_fp, cmd.c_str(), sizeof(char)*cmd.size());	
}
