#include "UcViewport.h"
#include "UcEvent.h"
NS_UNICORN;

GLViewport* GLViewport::_instance = NULL;

GLViewport::GLViewport()
{
	//UC_BREAK(initialize());
}


GLViewport::~GLViewport()
{
	UCSafeDelete(_instance);
}

GLViewport* GLViewport::getInstance()
{
	if (!_instance)
	{
		_instance = new GLViewport;
		if (!_instance)
		{
			UCSafeDelete(_instance);
			return NULL;
		}
	}
	return _instance;
}

bool GLViewport::initialize(std::string title, int w, int h)
{
	_width = w;
	_height = h;
	_title = title;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	_window = glfwCreateWindow( _width, _height, "UnicornEngine", nullptr, nullptr);
	glfwMakeContextCurrent(_window);

	// Set the required callback functions
	// entrance to initialize event sys
	glfwSetErrorCallback(&GLEvent::onGLError);
	glfwSetKeyCallback(_window, &GLEvent::onKeyCall);
	glfwSetScrollCallback(_window, &GLEvent::onScrollCall);
	glfwSetCursorPosCallback(_window, &GLEvent::onMouseMoveCall);

	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, 1);
		
	glewExperimental = GL_TRUE;
	glewInit();
	glViewport(0, 0, _width, _height);
	//

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_STENCIL_TEST);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	
	return true;
}//

bool GLViewport::shouldBeClosed()
{
	return glfwWindowShouldClose(_window) ? true : false;
}

//void GLViewport::onScrollCall(GLFWwindow* wnd, double x, double y)
//{
//	EventDispatcher::getInstance()->updateScrollFunc(wnd, x, y);
//}
//
//void GLViewport::onMouseMoveCall(GLFWwindow* wnd, double x, double y)
//{
//	EventDispatcher::getInstance()->updateMouseMoveFunc(wnd, x, y);
//}
//
//void GLViewport::onMousePressCall(GLFWwindow* wnd, int btn, int action, int modify)
//{
//	EventDispatcher::getInstance()->updateMousePressFunc(wnd, btn, action, modify);
//}
//
//void GLViewport::onKeyCall(GLFWwindow* wnd, int keyCode, int scanCode, int action, int mode)
//{
//	EventDispatcher::getInstance()->updateKeyFunc(wnd, keyCode, scanCode, action, mode);
//}

GLFWwindow* GLViewport::getWindow()
{
	return this->_window;
}

UCInline Size GLViewport::getWindowSize()
{
	return Size(_width, _height);
}


void GLViewport::destroy()
{

}