#ifndef IMAGECONVERSIONCOMMAND_H
#define IMAGECONVERSIONCOMMAND_H

#include "Command.h"

/**
 * Represents the command that converts an image from one format to another.
 */
class ImageConversionCommand : public Command {
public:
	ImageConversionCommand();
	/**
	 * Converts an image from one file format to another.
	 */
	CommandResult* execute(int argCount, std::string* args, ApplicationController* controller);
	bool match(int argCount, std::string* args);
};

#endif

