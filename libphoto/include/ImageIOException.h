#ifndef IMAGEIOEXCEPTION_H
#define IMAGEIOEXCEPTION_H

#include <exception>
#include <string>

/**
 * Represents an exception involving image IO.
 */
class ImageIOException : public std::exception {
public:
	ImageIOException(std::string message);
	virtual ~ImageIOException() throw();
	const char* what() const throw();

private:
	std::string m_message;
};

#endif

