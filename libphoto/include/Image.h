#ifndef IMAGE_H
#define IMAGE_H

#include "ColorData.h"
#include "PixelBuffer.h"

/**
 * Represents an image containing a width, height, and a set of pixels.
 */
class Image {
public:
	Image();
	Image(int width, int height, const ColorData* pixels);
	virtual ~Image();
	int getWidth() const;
	int getHeight() const;
	/**
	 * Applies this image to the given PixelBuffer, where (x, y) are the top left coordinates.
	 */
	void applyToBuffer(PixelBuffer* buffer, int x, int y) const;
	/**
	 * Returns the pixels that compose this image.
	 */
	ColorData const * const getData() const;
	friend bool operator== (const Image& a, const Image& b);

private:
	int m_width;
	int m_height;
	const ColorData* m_pixels;
};

#endif

