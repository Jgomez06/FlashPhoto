#ifndef IMAGECOMPARECOMMAND_H
#define IMAGECOMPARECOMMAND_H

#include "Command.h"

/**
 * Represents the command that compares two images.
 */
class ImageCompareCommand : public Command {
public:
	ImageCompareCommand();
	/**
	 * Compares two images.
	 */
	CommandResult* execute(int argCount, std::string* args, ApplicationController* controller);
	bool match(int argCount, std::string* args);
};

#endif

