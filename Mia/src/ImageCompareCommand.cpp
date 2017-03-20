#include "ImageCompareCommand.h"
#include <iostream>
#include "FailedCommandResult.h"
#include "SuccessfulCommandResult.h"
#include "ImageIOException.h"

ImageCompareCommand::ImageCompareCommand() {
}

CommandResult* ImageCompareCommand::execute(int argCount, std::string* args, ApplicationController* controller) {
	std::string imageName1(args[0]);
	std::string imageName2(args[2]);
	Image image1;
	Image image2;
	try {
		image1 = controller->loadImage(imageName1);
	} catch (ImageIOException& e) {
		return new FailedCommandResult("Invalid image " + imageName1);
	}

	try {
		image2 = controller->loadImage(imageName2);
	} catch (ImageIOException& e) {
		return new FailedCommandResult("Invalid image " + imageName2);
	}

	if (image1 == image2) {
		std::cout << "1" << std::endl;
	} else {
		std::cout << "0" << std::endl;
	}
	return new SuccessfulCommandResult();
}

bool ImageCompareCommand::match(int argCount, std::string* args) {
	if (argCount == 3 && args[1] == "-compare") {
		std::string imageName1(args[0]);
		std::string imageName2(args[2]);
		if (ApplicationController::isValidFileName(imageName1) && ApplicationController::isValidFileName(imageName2)) {
			std::string image1Extension = imageName1.substr(imageName1.find_last_of('.') + 1);
			std::string image2Extension = imageName2.substr(imageName2.find_last_of('.') + 1);
			return image1Extension == image2Extension;	
		}
	}
	return false;
}

