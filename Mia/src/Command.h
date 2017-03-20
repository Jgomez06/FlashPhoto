#ifndef COMMAND_H
#define COMMAND_H

#include "CommandResult.h"
#include <string>
#include "ApplicationController.h"

/**
 * Represents a command that can be executed on the command line, containing a certain set of arguments.
 */
class Command {
public:
	/**
	 * Called when the command is executed with the given arguments. Return a CommandResult based on whether the command was executed successfully.
	 */
	virtual CommandResult* execute(int argCount, std::string* args, ApplicationController* controller) = 0;
	/**
	 * Used for command matching in CommandHandler. Return true if this command matches the given arguments. Return false if otherwise.
	 */
	virtual bool match(int argCount, std::string* args) = 0;
};

#endif

