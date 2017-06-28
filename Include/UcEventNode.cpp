#include "UcEventNode.h"
NS_UNICORN;

Listener::Listener()
{

}

Listener::~Listener()
{

}

void Listener::onKeyPress(int keyCode, int scanCode, int mode)
{
	//Log("Function 'onKeyPress' is not be overrided in the driven class..\n");
}

void Listener::onKeyRelease(int keyCode, int scanCode, int mode)
{
	//Log("Function 'onKeyRelease' is not be overrided in the driven class..\n");
}

void Listener::onMouseMove(double x, double y)
{
	//Log("Function 'onMouseMove' is not be overrided in the driven class..\n");
}

void Listener::onMouseClick(int btn, int action, int modify)
{
	//Log("Function 'onMouseMove' is not be overrided in the driven class..\n");
}

void Listener::onScroll(double offX, double offY)
{
	//Log("Function 'onScroll' is not be overrided in the driven class..\n");
}
