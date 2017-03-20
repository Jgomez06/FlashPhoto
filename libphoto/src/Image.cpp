#include "Image.h"
#include "ColorData.h"
#include "PixelBuffer.h"

Image::Image(): m_width(0), m_height(0), m_pixels(new ColorData[0]) {
}

Image::Image(int width, int height, const ColorData* pixels): m_width(width), m_height(height), m_pixels(pixels) {
}
	
Image::~Image() {
	//delete [] m_pixels;
}

void Image::applyToBuffer(PixelBuffer* buffer, int x, int y) const {
	for (int i = 0; i < m_width; i++) {
		for (int j = 0; j < m_height; j++) {
			int xPos = x + i;
			int yPos = y + j;
			if (xPos < 0 || xPos >= buffer->getWidth() || yPos < 0 || yPos > buffer->getHeight()) {
				continue;			
			}
			buffer->setPixel(xPos, yPos, m_pixels[i + j * m_width]);
		}
	}
}

ColorData const * const Image::getData() const {
	return m_pixels;
}

int Image::getWidth() const {
	return m_width;
}

int Image::getHeight() const {
	return m_height;
}

bool operator== (const Image& a, const Image& b) {
	if (a.m_width == b.m_width && a.m_height == b.m_height) {
		for (int i = 0; i < a.m_width * a.m_height; i++) {
			if (a.m_pixels[i] != b.m_pixels[i]) {
				return false;		
			}
		}
		return true;
	}
	return false;
}

