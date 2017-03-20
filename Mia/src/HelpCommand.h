#ifndef HELPCOMMAND_H
#define HELPCOMMAND_H

#include "Command.h"

/**
 * Represents the help command (mia -h).
 */
class HelpCommand : public Command {
public:
	HelpCommand();
	/**
	 * Displays the help menu.
	 */
	CommandResult* execute(int argCount, std::string* args, ApplicationController* controller);
	bool match(int argCount, std::string* args);
	/**
	 * Helper method for displaying the help menu.
	 */
	static void displayHelp();
};

#endif

