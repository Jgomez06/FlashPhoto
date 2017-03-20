#ifndef JPEGIMAGEADAPTOR_H
#define JPEGIMAGEADAPTOR_H

#include "ImageAdaptor.h"

/**
 * Represents an adaptor for JPEG images.
 */
class JPEGImageAdaptor : public ImageAdaptor {
	public:	
		Image load(const std::string fileName);
		void save(const std::string fileName, Image image);
};

#endif

