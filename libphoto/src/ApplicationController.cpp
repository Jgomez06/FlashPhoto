#include "ApplicationController.h"
#include "ToolManager.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "CanvasManager.h"
#include "JPEGImageAdaptor.h"
#include "PNGImageAdaptor.h"
#include "Image.h"
#include <iostream>
#include <cstddef>
#include "ImageIOException.h"

ApplicationController::ApplicationController(int* width, int* height, int* curTool, ColorData* backgroundColor, PixelBuffer* displayBuffer, bool* theUndoReady, bool* theRedoReady) {
	m_width = width;
	m_height = height;
	m_curTool = curTool;
	m_undoReady = theUndoReady;
	m_redoReady = theRedoReady;
	m_backgroundColor = backgroundColor;
	m_displayBuffer = displayBuffer;
	m_currentColor = new ColorData(0, 0, 0);
	m_toolManager = new ToolManager(m_currentColor, m_curTool, m_backgroundColor);	
	m_canvasManager = new CanvasManager(m_displayBuffer, m_undoReady, m_redoReady);

	// Initialize ImageAdaptors
	JPEGImageAdaptor* jpegAdaptor = new JPEGImageAdaptor();
	m_imageAdaptors.insert(std::make_pair("jpg", jpegAdaptor));
	m_imageAdaptors.insert(std::make_pair("jpeg", jpegAdaptor));
	m_imageAdaptors.insert(std::make_pair("png", new PNGImageAdaptor()));
}

ApplicationController::ApplicationController() {
}

ApplicationController::~ApplicationController() {
	delete m_currentColor;
	delete m_backgroundColor;
	delete m_canvasManager;
	delete m_toolManager;
	delete m_undoReady;
	delete m_redoReady;
	delete m_width;
	delete m_height;
	delete m_curTool;
	m_imageAdaptors.clear();
}

void ApplicationController::mouseDragged(int x, int y) {
	m_toolManager->useCurrentTool(x, y, DRAG, m_displayBuffer, m_previousX, m_previousY);
	m_previousX = x;
	m_previousY = y;
}

void ApplicationController::leftMouseDown(int x, int y, float red, float green, float blue) {
	// Update ColorData pointer so current Tool can use it if necessary 
	*m_currentColor = ColorData(red, green, blue);
	m_toolManager->useCurrentTool(x, y, CLICK, m_displayBuffer, m_previousX, m_previousY);
	m_previousX = x;
	m_previousY = y;
}

void ApplicationController::leftMouseUp(int x, int y) {
	saveCanvas();
}

void ApplicationController::applyFilterToBuffer(Filter* filter) {
	applyFilterToBuffer(filter, m_displayBuffer);
	saveCanvas();
}

void ApplicationController::applyFilterToBuffer(Filter* filter, PixelBuffer* buffer) {
	filter->applyToBuffer(buffer);
}

bool ApplicationController::undo() {
	return changeBuffer(m_canvasManager->undo());
}       

bool ApplicationController::redo() {
	return changeBuffer(m_canvasManager->redo());
}

bool ApplicationController::changeBuffer(PixelBuffer* newBuffer) {
	int newWidth = newBuffer->getWidth();
	int newHeight = newBuffer->getHeight();
	if (m_displayBuffer->getWidth() != newWidth || m_displayBuffer->getHeight() != newHeight) {
		std::cout << "size change required" << std::endl;
		*m_displayBuffer = *newBuffer;
		return true;
	} else {
		std::cout << "no size change" << std::endl;
		PixelBuffer::copyPixelBuffer(newBuffer, m_displayBuffer);
		return false;
	}
}

Image ApplicationController::loadImage(const std::string& fileName) {
	if (!isValidFileName(fileName)) {
		throw ImageIOException("Cannot load invalid image file " + fileName);
	} else {
		return getAdaptorFromFileName(fileName)->load(fileName);
	}
}

ImageAdaptor* ApplicationController::getAdaptorFromFileName(const std::string fileName) {
	std::string extension = fileName.substr(fileName.find_last_of('.') + 1);
	std::map<std::string, ImageAdaptor*>::iterator it = m_imageAdaptors.find(extension);
	return it->second;
}

void ApplicationController::saveCanvas() {
	m_canvasManager->saveCanvas();
}

void ApplicationController::loadImageToStamp(const std::string& fileName) {
	Image image = loadImage(fileName);
	m_toolManager->setStampImage(image);
}

void ApplicationController::saveImage(const std::string& fileName, Image image) {
	if (!isValidFileName(fileName)) {
		throw ImageIOException("Cannot save invalid image file " + fileName);
	} else {
		getAdaptorFromFileName(fileName)->save(fileName, image);
	}
}

void ApplicationController::addTool(Tool* tool) {
	m_toolManager->addTool(tool);
}

ColorData ApplicationController::getColorFromKernel(int x, int y, const PixelBuffer& buffer, const float* kernel, int kernelSize, float factor, float bias) {
	int bufferWidth = buffer.getWidth();
	int bufferHeight = buffer.getHeight();
	int offset = kernelSize / 2;
	float red = 0;
	float green = 0;
	float blue = 0;
	// Iterate over the kernel and neighboring pixels, with each neighbor pixel having an influence on each component of the new color based on the kernel value
	for (int i = 0; i < kernelSize; i++) {
		for (int j = 0; j < kernelSize; j++) {
			// (xPos,yPos) are absolute buffer coordinates, modulo divided by the buffer dimensions so that the coordinates "wrap" if necessary.
			int xPos = (x - offset + i + bufferWidth) % bufferWidth;
			int yPos = (y - offset + j + bufferHeight) % bufferHeight;
			ColorData color = buffer.getPixel(xPos, yPos);
			float modifier = kernel[i + j * kernelSize];
			red += color.getRed() * modifier;
			green += color.getGreen() * modifier;
			blue += color.getBlue() * modifier;
		}
	}

	red = factor * red + bias;
	green = factor * green + bias;
	blue = factor * blue + bias;
	ColorData color(red, green, blue);
	return color.clampedColor(); // Ensure values lay between 0.0 and 1.0	
}

bool ApplicationController::isValidFileName(const std::string fileName) {
	int index = fileName.find_last_of('.') + 1;
	std::string extension = fileName.substr(index);
	return extension == "jpeg" || extension == "jpg" || extension == "png";
}

