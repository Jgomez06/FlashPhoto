#include "ImageIOException.h"

ImageIOException::ImageIOException(std::string message): m_message(message) {
}

ImageIOException::~ImageIOException() throw() {
}

const char* ImageIOException::what() const throw() {
	std::string errorMessage("[libphoto] " + m_message);
	return errorMessage.c_str();
}

