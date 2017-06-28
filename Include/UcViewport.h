#ifndef GLVIEWPORT_H
#define GLVIEWPORT_H
//
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "UcObject.h"
#include "UcSize.h"
#include "UcEventDispatcher.h"

namespace Unicorn
{
//
	class GLViewport: public Object
	{
	public:
		~GLViewport();	
		static GLViewport* getInstance();
		//
		bool initialize(std::string title, int w, int h);
		//
		bool shouldBeClosed();
		//
/*		void onKeyCall(GLFWwindow* wnd, int keyCode, int scanCode, int action, int mode);
		void onScrollCall(GLFWwindow* wnd, double x, double y);
		void onMousePressCall(GLFWwindow* wnd, int btn, int action, int modify);
		void onMouseMoveCall(GLFWwindow* wnd, double x, double y);
	*/	//
		GLFWwindow* getWindow();
		UCInline unsigned short getWindowWidth(){ return _width; }
		UCInline unsigned short getWindowHeight(){ return _height; }
		UCInline Size getWindowSize();
		//
		virtual void destroy();

		

	private:
		GLViewport();
		
	private:
		static GLViewport* _instance;
		GLFWwindow* _window;
		std::string _title;
		unsigned short _width;
		unsigned short _height;
	};

}

#endif
