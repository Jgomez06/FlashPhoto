#ifndef COMMANDRESULT_H
#define COMMANDRESULT_H

/**
 * Represents some result of executing a command.
 */
class CommandResult {
public:
	/**
	 * Called after a command is executed. Subclasses can implement some behavior for after a command has been executed.
	 */
	virtual void run() = 0;
};

#endif

