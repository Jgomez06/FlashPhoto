#ifndef PNGIMAGEADAPTOR_H
#define PNGIMAGEADAPTOR_H

#include "ImageAdaptor.h"

/**
 * Represents an adaptor for PNG images.
 */
class PNGImageAdaptor : public ImageAdaptor {
public:
	Image load(const std::string fileName);
	void save(const std::string fileName, Image image);
};

#endif

