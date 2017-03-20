#ifndef SUCCESSFULCOMMANDRESULT_H
#define SUCCESSFULCOMMANDRESULT_H

#include "CommandResult.h"

/**
 * Represents a command that executed successfully. This class does nothing after the command has finished executing (silent success).
 */
class SuccessfulCommandResult : public CommandResult {
public:
	SuccessfulCommandResult();
	void run();
};

#endif

