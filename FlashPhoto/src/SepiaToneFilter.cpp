#include "SepiaToneFilter.h"
#include "ColorData.h"

SepiaToneFilter::SepiaToneFilter() {
}

SepiaToneFilter::~SepiaToneFilter() {
}

ColorData SepiaToneFilter::convertPixel(ColorData pixel) {
	float red = pixel.getRed();
	float green = pixel.getGreen();
	float blue = pixel.getBlue();
	float newRed = red * 0.393 + green * 0.796 + blue * 0.189;
	float newGreen = red * 0.349 + green * 0.686 + blue * 0.168;
	float newBlue = red * 0.272 + green * 0.534 + blue * 0.131;
	return ColorData(newRed, newGreen, newBlue).clampedColor(); 
}

