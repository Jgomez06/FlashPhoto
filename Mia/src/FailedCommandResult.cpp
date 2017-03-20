#include "FailedCommandResult.h"
#include <iostream>
#include "HelpCommand.h"

FailedCommandResult::FailedCommandResult(std::string errorMessage): m_errorMessage(errorMessage) {
}

void FailedCommandResult::run() {
	std::cout << "Failed to execute command: " << m_errorMessage << std::endl;
	HelpCommand::displayHelp();
}

