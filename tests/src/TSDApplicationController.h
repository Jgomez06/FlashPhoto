#ifndef TSDAPPLICATIONCONTROLLER_H
#define TSDAPPLICATIONCONTROLLER_H

#include "ApplicationController.h"
#include "Tool.h"


class TSDApplicationController : public ApplicationController 
{
public:
	TSDApplicationController();

	virtual ~TSDApplicationController();

private:

	Tool* m_tool;
};
#endif 
