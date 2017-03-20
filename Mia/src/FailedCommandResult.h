#ifndef FAILEDCOMMANDRESULT_H
#define FAILEDCOMMANDRESULT_H

#include "CommandResult.h"
#include <string>

/**
 * Represents a command that failed to execute for some reason. This class prints the specified error message after the command has finished executing.
 */
class FailedCommandResult : public CommandResult {
public:
	FailedCommandResult(std::string errorMessage);
	void run();

private:
	std::string m_errorMessage;
};

#endif

