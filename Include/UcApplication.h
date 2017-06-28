#ifndef APPLICATION_H
#define APPLICATION_H
//
#include "UcMacros.h"

namespace Unicorn{

class Application
{
public:
	enum RunningState{
		RS_EXIT, RS_NORMAL, RS_PAUSE, RS_ERROR, RS_FINISH
	};

	//
	virtual bool onAppLaunched() { return true; }
	//
	virtual bool onAppFinished() { return true;  }
	//
	virtual int run(){ return 1; };
	//
	virtual ~Application();
};

}

#endif