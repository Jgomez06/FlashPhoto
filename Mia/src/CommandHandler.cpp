#include "CommandHandler.h"
#include <iostream>
#include "HelpCommand.h"
#include "ImageConversionCommand.h"
#include "ImageCompareCommand.h"
#include "ImageFilterCommand.h"

CommandHandler::CommandHandler() {
	m_commands.push_back(new HelpCommand());
	m_commands.push_back(new ImageConversionCommand());
	m_commands.push_back(new ImageCompareCommand());
	m_commands.push_back(new ImageFilterCommand());
}

CommandHandler::~CommandHandler() {
	for (std::vector<Command*>::iterator it = m_commands.begin(); it != m_commands.end(); ++it) {
		delete (*it);
	}
	m_commands.clear();
}

void CommandHandler::handleCommand(int argCount, char* args[], ApplicationController* controller) {
	// Convert arguments into a nicer string array, skipping the first argument
	int cmdArgsSize = argCount - 1;
	std::string* cmdArgs = new std::string[cmdArgsSize];
	for (int i = 1; i < argCount; i++) {
		cmdArgs[i - 1] = args[i];
	}

	// Attempt to match and execute the command
	Command* command;
	bool found = false;
	for (std::vector<Command*>::iterator it = m_commands.begin(); it != m_commands.end(); ++it) {
    		command = *it;
		if (command->match(cmdArgsSize, cmdArgs)) {
			CommandResult* result = command->execute(cmdArgsSize, cmdArgs, controller);
			result->run();
			delete result;
			found = true;
		}
	}

	// Display help if command was not found
	if (!found) {
		std::cout << "Invalid command 'mia";
		for (int i = 0; i < cmdArgsSize; i++) {
			std::cout << " " << cmdArgs[i];
		}
		std::cout << "':" << std::endl;
		HelpCommand::displayHelp();
	}
}

