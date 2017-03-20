#ifndef IMAGEFILTERCOMMAND_H
#define IMAGEFILTERCOMMAND_H

#include "Command.h"
#include <string>
#include <vector>

/**
 * Represents the command that applies filters to an image.
 */
class ImageFilterCommand : public Command {
public:
	ImageFilterCommand();
	/**
	 * Applies filters to an image and outputs a new file.
	 */
	CommandResult* execute(int argCount, std::string* args, ApplicationController* controller);
	bool match(int argCount, std::string* args);

private:
	bool isDirectory(std::string fileName);
	bool isValidFilterArgument(std::string arg);
	std::vector<std::string> split(const std::string &text, char sep);
	std::vector<std::string> m_validFilters;
};

#endif

