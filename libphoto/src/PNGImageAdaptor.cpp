#include <png.h>
#include <cstring>

#include "PNGImageAdaptor.h"
#include "ColorData.h"
#include "ImageIOException.h"

Image PNGImageAdaptor::load(const std::string fileName) {
	png_image pngImage;
	memset(&pngImage, 0, (sizeof pngImage));
	pngImage.version = PNG_IMAGE_VERSION;

	int red;
	int green;
	int blue;
	int alpha;
	ColorData* pixels;
	if (png_image_begin_read_from_file(&pngImage, fileName.c_str())) {
		pixels = new ColorData[pngImage.width * pngImage.height];
		pngImage.format = PNG_FORMAT_RGBA;
		png_bytep buffer = new png_byte[PNG_IMAGE_SIZE(pngImage)];
		if (buffer && png_image_finish_read(&pngImage, NULL, buffer, 0, NULL)) {
			for (int y = 0; y < pngImage.height; y++) {
				for (int x = 0; x < pngImage.width; x++) {
					red = (int) buffer[(y * pngImage.width * 4) + (x * 4)];
					green = (int) buffer[(y * pngImage.width * 4) + (x * 4) + 1];
					blue = (int) buffer[(y * pngImage.width * 4) + (x * 4) + 2];
					alpha = (int) buffer[(y * pngImage.width * 4) + (x * 4) + 3];
					pixels[x + (pngImage.height - y - 1) * pngImage.width] = ColorData(red / 255.0, green / 255.0, blue / 255.0, alpha / 255.0);
				}
			}
		}

		delete [] buffer;
	} else {
		throw ImageIOException("Could not load PNG file " + fileName);
	}

	return Image(pngImage.width, pngImage.height, pixels);
}

void PNGImageAdaptor::save(const std::string fileName, Image image) {
	png_image pngImage;
	memset(&pngImage, 0, (sizeof pngImage));
	pngImage.width = image.getWidth();
	pngImage.height = image.getHeight();
	pngImage.version = PNG_IMAGE_VERSION;
	pngImage.opaque = NULL;
	pngImage.format = PNG_FORMAT_RGBA;
	png_bytep buffer = new png_byte[PNG_IMAGE_SIZE(pngImage)];

	const ColorData* pixels = image.getData();
	for (int y = pngImage.height - 1; y >= 0; y--) {
		for (int x = 0; x < pngImage.width; x++) {
			ColorData color = pixels[x + y * pngImage.width];
			buffer[((pngImage.height - (y + 1)) * pngImage.width + x) * 4] = (png_byte) (color.getRed() * 255.0);
			buffer[((pngImage.height - (y + 1)) * pngImage.width + x) * 4 + 1] = (png_byte) (color.getGreen() * 255.0);
			buffer[((pngImage.height - (y + 1)) * pngImage.width + x) * 4 + 2] = (png_byte) (color.getBlue() * 255.0);
			buffer[((pngImage.height - (y + 1)) * pngImage.width + x) * 4 + 3] = (png_byte) (color.getAlpha() * 255.0);
		}
	}

	png_image_write_to_file(&pngImage, fileName.c_str(), 0, buffer, 0, NULL);
	delete [] buffer;
	
}

