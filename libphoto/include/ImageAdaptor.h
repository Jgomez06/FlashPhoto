#ifndef IMAGEADAPTOR_H
#define IMAGEADAPTOR_H

#include "Image.h"
#include <string>

/**
 * Serves as an adaptor class for image loading and saving. To support an image extension, extend this class and implement load and
 * save as required by the image library.
 */
class ImageAdaptor {
	public:
		/**
		 * Subclasses should implement this method to load an image from the given file
		 */
		virtual Image load(const std::string fileName) = 0;
		/**
		 * Subclasses should implement this method to save an image to the given file
		 */
		virtual void save(const std::string fileName, Image image) = 0;
};

#endif

