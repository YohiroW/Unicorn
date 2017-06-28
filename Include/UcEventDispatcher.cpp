#include "UcEventDispatcher.h"
#include "UcEventNode.h"
NS_UNICORN;

EventDispatcher* EventDispatcher::_instance = NULL;

EventDispatcher::EventDispatcher()
{
}

EventDispatcher::~EventDispatcher()
{
	UCSafeDelete(_instance);
}

EventDispatcher* EventDispatcher::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new EventDispatcher;
	}
	return _instance;
}

bool EventDispatcher::initialize()
{


	return true;
}

void EventDispatcher::updateKeyFunc(GLFWwindow* wnd, int key, int scancode, int action, int mode)
{
	Node<Listener*>* p = _eventList.getLinkHead()->next;
	while (p)
	{
		if (action == GLFW_PRESS)
			p->elem->onKeyPress(key, scancode, mode);
		else if (action == GLFW_RELEASE)
			p->elem->onKeyRelease(key, scancode, mode);

		p = p->next;
	}
}

void EventDispatcher::updateMouseMoveFunc(GLFWwindow* wnd, double x, double y)
{
	Node<Listener*>* p = _eventList.getLinkHead()->next;
	while (p)
	{
		p->elem->onMouseMove(x, y);
		p = p->next;
	}
}

void EventDispatcher::updateMousePressFunc(GLFWwindow* wnd, int btn, int action, int modify)
{
	Node<Listener*>* p = _eventList.getLinkHead()->next;
	while (p)
	{
		p->elem->onMouseClick(btn, action, modify);
		p = p->next;
	}
}

void EventDispatcher::updateScrollFunc(GLFWwindow* wnd, double x, double y)
{
	Node<Listener*>* p = _eventList.getLinkHead()->next;
	while (p)
	{
		p->elem->onScroll(x, y);
		p = p->next;
	}

}

void EventDispatcher::addListener(Listener* listener)
{
	_eventList.append(listener);
}

void EventDispatcher::removeListener(Listener* listener)
{
	_eventList.remove(listener);
}


