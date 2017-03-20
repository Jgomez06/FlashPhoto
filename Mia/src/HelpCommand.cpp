#include "HelpCommand.h"
#include <iostream>
#include "SuccessfulCommandResult.h"

HelpCommand::HelpCommand() {
}

CommandResult* HelpCommand::execute(int argCount, std::string* args, ApplicationController* controller) {
	displayHelp();
	return new SuccessfulCommandResult();
}

bool HelpCommand::match(int argCount, std::string* args) {
	return argCount >= 1 && args[0] == "-h";
}

void HelpCommand::displayHelp() {
	std::cout << "================================================================" << std::endl;
	std::cout << "mia -h -- Displays this menu" << std::endl;
	std::cout << "mia <input-file>.jpg <output-file>.png  -- Converts from JPEG to PNG" << std::endl;
	std::cout << "mia <input-file>.png <output-file>.jpg  -- Converts from PNG to JPEG" << std::endl;
	std::cout << "mia <file-one> -compare <file-two>  -- Compares two files, printing 1 if equal and 0 if not" << std::endl;
	std::cout << "mia <input-file> <filter-arguments> <output-file>  -- Applies filters to the image in the order specified" << std::endl;
	std::cout << "mia <input-directory> <filter-arguments> <output-directory>  -- Applies filters to all images in the directory" << std::endl;
	std::cout << "    Valid Filter Arguments:" << std::endl;
	std::cout << "        -sharpen <amount>" << std::endl;
	std::cout << "        -edgedetect" << std::endl;
	std::cout << "        -thresh <amount>" << std::endl;
	std::cout << "        -quantize <bins>" << std::endl;
	std::cout << "        -blur <amount>" << std::endl;
	std::cout << "        -multrgb <red-multiplier>,<green-multiplier>,<blue-multiplier>" << std::endl;
	std::cout << "        -saturate <amount>" << std::endl;
	std::cout << "    Example: mia image.png -sharpen 5 -thresh 0.2 multrgb 0.0,0.8,0.0 newimage.png" << std::endl;
	std::cout << "================================================================" << std::endl;
}

