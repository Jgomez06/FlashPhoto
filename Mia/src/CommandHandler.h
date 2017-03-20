#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <vector>
#include "Command.h"
#include "ApplicationController.h"

/**
 * Class for handling command-line arguments.
 */
class CommandHandler {
public:
	CommandHandler();
	virtual ~CommandHandler();
	/**
	 * Handles the passed command arguments.
	 */
	void handleCommand(int argCount, char* args[], ApplicationController* controller);

private:
	/**
	 * List of valid commands.
	 */
	std::vector<Command*> m_commands;
};

#endif

