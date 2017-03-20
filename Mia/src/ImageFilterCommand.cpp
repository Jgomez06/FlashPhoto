#include "ImageFilterCommand.h"
#include <iostream>
#include "FailedCommandResult.h"
#include "SuccessfulCommandResult.h"
#include "ImageIOException.h"
#include <algorithm>
#include "SharpenFilter.h"
#include "EdgeDetectFilter.h"
#include "QuantizeFilter.h"
#include "ThresholdFilter.h"
#include "SaturationFilter.h"
#include "BlurFilter.h"
#include "RGBFilter.h"
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>

ImageFilterCommand::ImageFilterCommand() {
	m_validFilters.reserve(7);
	m_validFilters.push_back("sharpen");
	m_validFilters.push_back("edgedetect");
	m_validFilters.push_back("thresh");
	m_validFilters.push_back("quantize");
	m_validFilters.push_back("blur");
	m_validFilters.push_back("saturate");
	m_validFilters.push_back("multrgb");
}

CommandResult* ImageFilterCommand::execute(int argCount, std::string* args, ApplicationController* controller) {
	std::string inputFile(args[0]);
	std::string outputFile(args[argCount - 1]);
	std::vector<Filter*> filters;
	for (int i = 1; i < argCount - 1; i++) {
		std::string filterArg = args[i];
		std::string filter = filterArg.substr(1);
		if (isValidFilterArgument(filterArg)) {
			std::string nextArg = args[i + 1];
			if (filter == "sharpen") {
				int amount;
				std::istringstream convert(nextArg);
				if (!(convert >> amount)) {
					return new FailedCommandResult("sharpen requires an integer amount");
				}
				filters.push_back(new SharpenFilter(amount));
				i++;
			} else if (filter == "edgedetect") {
				if (nextArg.compare(0, 1, "-") != 0 && i != argCount - 2) {
					return new FailedCommandResult("edgedetect must take no arguments");
				}
				filters.push_back(new EdgeDetectFilter());
			} else if (filter == "thresh") {
				float amount;
				std::istringstream convert(nextArg);
				if (!(convert >> amount)) {
					return new FailedCommandResult("thresh requires a float amount");
				}
				filters.push_back(new ThresholdFilter(amount));
				i++;
			} else if (filter == "quantize") {
				int bins;
				std::istringstream convert(nextArg);
				if (!(convert >> bins)) {
					return new FailedCommandResult("quantize requires an integer bin amount");
				}
				filters.push_back(new QuantizeFilter(bins));
				i++;
			} else if (filter == "blur") {
				float amount;
				std::istringstream convert(nextArg);
				if (!(convert >> amount)) {
					return new FailedCommandResult("blur requires a float amount");
				}
				filters.push_back(new BlurFilter(amount));
				i++;
			} else if (filter == "saturate") {
				float amount;
				std::istringstream convert(nextArg);
				if (!(convert >> amount)) {
					return new FailedCommandResult("saturate requires a float amount");
				}
				filters.push_back(new SaturationFilter(amount));
				i++;
			} else if (filter == "multrgb") {
				std::vector<std::string> valueStrings = split(nextArg, ',');
				if (valueStrings.size() != 3) {
					return new FailedCommandResult("multrgb requires three floats");
				}
				float red;
				std::istringstream convert(valueStrings.at(0));
				if (!(convert >> red)) {
					return new FailedCommandResult("multrgb requires three floats");
				}
				float green;
				std::istringstream convert2(valueStrings.at(1));
				if (!(convert2 >> green)) {
					return new FailedCommandResult("multrgb requires three floats");
				}
				float blue;
				std::istringstream convert3(valueStrings.at(2));
				if (!(convert3 >> blue)) {
					return new FailedCommandResult("multrgb requires three floats");
				}
				filters.push_back(new RGBFilter(red, green, blue));
				i++;
			}
		} else {
			return new FailedCommandResult("Invalid filter argument '" + filter + "'");
		}
	}

	bool isDir = false;
	std::vector<std::string> imageNames;
	if (isDirectory(inputFile)) {
		DIR* dir;
		struct dirent* ent;
		if ((dir = opendir(inputFile.c_str())) != NULL) {
			while ((ent = readdir(dir)) != NULL) {
				std::string fileName = ent->d_name;
				if (ApplicationController::isValidFileName(fileName)) {
					imageNames.push_back(fileName);
				}
			}
			closedir(dir);
		}
		isDir = true;
	} else {
		imageNames.push_back(inputFile);
	}

	// Create directory if necessary
	if (isDir) {
		mkdir(outputFile.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}

	for (std::vector<std::string>::iterator it = imageNames.begin(); it != imageNames.end(); it++) {
		std::string fileName = *it;
		Image image;
		try {
			std::string name(fileName);
			if (isDir) {
				name = inputFile + "/" + fileName;
			}
			image = controller->loadImage(name);
		} catch (ImageIOException& e) {
			return new FailedCommandResult("Invalid image " + fileName);
		}

		// Convert image to PixelBuffer so that filters can be applied
		int width = image.getWidth();
		int height = image.getHeight();
		PixelBuffer* buffer = new PixelBuffer(width, height, new ColorData(0, 0, 0));
		image.applyToBuffer(buffer, 0, 0);
		
		// Apply all filters in order
		for (std::vector<Filter*>::iterator fit = filters.begin(); fit != filters.end(); fit++) {
			Filter* filter = *fit;
			controller->applyFilterToBuffer(filter, buffer);
		}

		// Convert back to Image
		ColorData* pixels = new ColorData[width * height];
		for (int i = 0; i < width * height; i++) {
			pixels[i] = buffer->getPixel(i % width, i / width);
		}

		std::string name(outputFile);
		if (isDir) {
			name = outputFile + "/" + fileName;
		}
		Image filteredImage(width, height, pixels);
		controller->saveImage(name, filteredImage);

		delete buffer;
		delete pixels;
	}

	return new SuccessfulCommandResult();
}

bool ImageFilterCommand::match(int argCount, std::string* args) {
	if (argCount >= 3) {
		std::string imageName1(args[0]);
		std::string imageName2(args[argCount - 1]);
		if (isValidFilterArgument(args[1])) { // Check just first filter for matching purposes
			return (ApplicationController::isValidFileName(imageName1) && ApplicationController::isValidFileName(imageName2))
					|| isDirectory(imageName1);
		}

	}
	return false;
}

bool ImageFilterCommand::isDirectory(std::string fileName) {
	DIR* dir;
	if ((dir = opendir(fileName.c_str())) != NULL) {
		closedir(dir);
		return true;
	}
	return false;
}

bool ImageFilterCommand::isValidFilterArgument(std::string arg) {
	if (arg.compare(0, 1, "-") == 0) {
		arg = arg.substr(1);
		return std::find(m_validFilters.begin(), m_validFilters.end(), arg) != m_validFilters.end();
	}
	return false;
}

// http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string> ImageFilterCommand::split(const std::string &text, char sep) {
	std::vector<std::string> tokens;
	std::size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != std::string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}

