#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H
//
#include <list>
#include <vector>
#include <functional>
#include <GLFW/glfw3.h>
#include "UcMacros.h"
#include "UcConfig.h"
#include "UcLinkList.h"

namespace Unicorn
{
	class Listener; 

	class EventDispatcher
	{
	public:
		typedef struct  EventNode
		{
			Listener* listener;
			EventNode* next;

		}EventNode;


	public:
		//
		virtual ~EventDispatcher();
		//
		static EventDispatcher* getInstance();
		//
		bool initialize();
		//
		void updateMousePressFunc(GLFWwindow* wnd, int btn, int action, int modify);
		void updateMouseMoveFunc(GLFWwindow* wnd, double x, double y);
		void updateScrollFunc(GLFWwindow* wnd, double x, double y);
		void updateKeyFunc(GLFWwindow* wnd, int key, int scancode, int action, int mode);
		//
		void addListener(Listener* listener);
		void removeListener(Listener* listener);

	private:
		EventDispatcher();
		//
		void _updateEvents();
		//
		LinkList<Listener*> _eventList;		
		//
		static EventDispatcher* _instance;
		//
		static bool _keys[1024];

	};

}
#endif

