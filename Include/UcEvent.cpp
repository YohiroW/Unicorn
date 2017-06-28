#include "UcEvent.h"

NS_UNICORN;

GLViewport* GLEvent::_viewport = nullptr;

void GLEvent::setViewport(GLViewport* view)
{
	if (view)
		_viewport = view;
}

void GLEvent::onGLError(int errorID, const char* errorDesc)
{
	//if (_viewport)
	//{
	//	_viewport->
	//}
}

void GLEvent::onKeyCall(GLFWwindow* wnd, int keyCode, int scanCode, int action, int mode)
{
	if (_viewport)
	{
		EventDispatcher::getInstance()->updateKeyFunc(wnd, keyCode, scanCode, action, mode);
	}
}

void GLEvent::onScrollCall(GLFWwindow* wnd, double x, double y)
{
	if (_viewport)
	{
		EventDispatcher::getInstance()->updateScrollFunc(wnd, x, y);
	
	}
}

void GLEvent::onMousePressCall(GLFWwindow* wnd, int btn, int action, int modify)
{
	if (_viewport)
	{
		EventDispatcher::getInstance()->updateMousePressFunc(wnd, btn, action, modify);
	}
}

void GLEvent::onMouseMoveCall(GLFWwindow* wnd, double x, double y)
{
	if (_viewport)
	{
		EventDispatcher::getInstance()->updateMouseMoveFunc(wnd, x, y);
	}
}

void GLEvent::keyDidPressed()
{

}

int GLEvent::getKeyState(const int& keycode)
{
	return glfwGetKey(_viewport->getWindow(), keycode);
}

int GLEvent::getMouseState(const int& btn)
{
	return glfwGetMouseButton(_viewport->getWindow(), btn);
}
