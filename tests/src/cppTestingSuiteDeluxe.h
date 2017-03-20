#ifndef CPPTESTINGSUITE_H
#define CPPTESTINGSUITE_H

#include <vector>
#include "PixelBuffer.h"
#include "MaskTool.h"

class cppTestingSuite 
{	
public:
	bool validateInput(int& argc, char* argv[]);
	Tool* getTool(char *toolName);
	Image simulateCmds(char* cmdFile);
	std::string m_toolType;

private: 

	bool hasSuffix(const std::string & str, const std::string & suffix);
	std::vector<std::string> split(std::string s, char delim);

	Tool* m_tool;
};

#endif
