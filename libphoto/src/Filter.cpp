#include "Filter.h"
#include "ColorData.h"

void Filter::applyToBuffer(PixelBuffer* buffer) {
	int width = buffer->getWidth();
	int height = buffer->getHeight();
	ColorData* pixels = new ColorData[width * height];
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			pixels[x + y * width] = calculate(x, y, buffer);
		}
	}

	// Modify PixelBuffer after all new pixel colors have been calculated
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			buffer->setPixel(x, y, pixels[x + y * width]);
		}
	}
	delete [] pixels;
}

