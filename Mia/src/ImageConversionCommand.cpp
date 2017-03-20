#include "ImageConversionCommand.h"
#include <iostream>
#include "SuccessfulCommandResult.h"
#include "FailedCommandResult.h"
#include "ImageIOException.h"

ImageConversionCommand::ImageConversionCommand() {
}

CommandResult* ImageConversionCommand::execute(int argCount, std::string* args, ApplicationController* controller) {
	std::string inputFile(args[0]);
	std::string outputFile(args[1]);
	Image image;
	try {
		image = controller->loadImage(inputFile);
	} catch (ImageIOException& e) {
		return new FailedCommandResult("Invalid image " + inputFile);
	}

	controller->saveImage(outputFile, image);
	return new SuccessfulCommandResult();
}

bool ImageConversionCommand::match(int argCount, std::string* args) {
	if (argCount == 2) {
		std::string inputFile(args[0]);
		std::string outputFile(args[1]);
		if (ApplicationController::isValidFileName(inputFile) && ApplicationController::isValidFileName(outputFile)) {
			std::string inputExtension = inputFile.substr(inputFile.find_last_of('.') + 1);
			std::string outputExtension = outputFile.substr(outputFile.find_last_of('.') + 1);
			return inputExtension != outputExtension;
		}
	}
	return false;
}

