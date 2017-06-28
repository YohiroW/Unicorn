#ifndef  EVENT_H
#define  EVENT_H
//
#include "UcMacros.h"
#include "UcViewport.h"

namespace Unicorn
{
	enum EventType
	{
		ET_MOUSE_HOVER,
		ET_MOUSE_PRESS,
		ET_MOUSE_FINISH,
		ET_MOUSE_SCROLL,
		ET_KEYBOARD_PRESS,
		ET_KEYBOARD_FINISH
	};

	enum KeyCode
	{
		KEY_UNKNOW = -1, 
		KEY_SPACE = 32,
		KEY_APOSTROPHE = 39,	/* ' */
 		KEY_COMMA = 44,			/* , */
 		KEY_MINUS = 45,			/* - */
 		KEY_PERIOD = 46,		/* . */
 		KEY_SLASH = 47,			/* / */
 		KEY_0 = 48,
 		KEY_1, 
 		KEY_2,  
 		KEY_3,  
 		KEY_4,   
 		KEY_5,   
 		KEY_6,   
 		KEY_7,   
 		KEY_8,   
 		KEY_9,
 		KEY_SEMICOLON = 59,    /* ; */
 		KEY_EQUAL = 61,        /* = */
 		KEY_A = 65,
 		KEY_B,  
 		KEY_C,  
 		KEY_D,  
 		KEY_E,  
 		KEY_F, 
 		KEY_G,  
 		KEY_H,  
 		KEY_I, 
 		KEY_J,  
 		KEY_K,   
 		KEY_L,   
 		KEY_M,   
 		KEY_N,   
 		KEY_O,   
 		KEY_P,   
		KEY_Q,
 		KEY_R,  
 		KEY_S ,  
 		KEY_T, 
 		KEY_U,
 		KEY_V,
 		KEY_W,
 		KEY_X,
 		KEY_Y,
 		KEY_Z,   
 		KEY_LEFT_BRACKET,   		/* [ */
 		KEY_BACKSLASH,   			/* \ */
 		KEY_RIGHT_BRACKET,		    /* ] */
 		KEY_GRAVE_ACCENT = 96,		/* ` */
 		KEY_WORLD_1 = 161,		 /* non-US #1 */
 		KEY_WORLD_2,     		 /* non-US #2 */
 		KEY_ESCAPE = 256,
 		KEY_TAB = 258,
 		KEY_BACKSPACE,
 		KEY_INSERT, 
 		KEY_DELETE, 
 		KEY_RIGHT,  
 		KEY_LEFT,  
 		KEY_DOWN,  
 		KEY_UP,   
 		KEY_PAGE_UP,  
 		KEY_PAGE_DOWN,  
 		KEY_HOME,  
 		KEY_END,   
 		KEY_CAPS_LOCK = 280,
 		KEY_SCROLL_LOCK, 
 		KEY_NUM_LOCK,  
 		KEY_PRINT_SCREEN,  
 		KEY_PAUSE,   
 		KEY_F1 = 290,
 		KEY_F2,
 		KEY_F3,
 		KEY_F4,
 		KEY_F5,
 		KEY_F6,
 		KEY_F7,
 		KEY_F8,
 		KEY_F9, 
 		KEY_F10,   
 		KEY_F11,  
 		KEY_F12,  
 		KEY_F13,  
 		KEY_F14,  
 		KEY_F15,  
 		KEY_F16,  
 		KEY_F17,  
 		KEY_F18,  
 		KEY_F19,  
 		KEY_F20,  
 		KEY_F21,  
 		KEY_F22,  
 		KEY_F23,  
 		KEY_F24,  
 		KEY_F25,
 		KEY_KP_0 = 320,
 		KEY_KP_1,
 		KEY_KP_2,
 		KEY_KP_3,
 		KEY_KP_4,
 		KEY_KP_5,
 		KEY_KP_6,
 		KEY_KP_7,
 		KEY_KP_8,
 		KEY_KP_9,
 		KEY_KP_DECIMAL,
 		KEY_KP_DIVIDE,
 		KEY_KP_MULTIPLY,
 		KEY_KP_SUBTRACT,
 		KEY_KP_ADD,
 		KEY_KP_ENTER,
 		KEY_KP_EQUAL,
 		KEY_LEFT_SHIFT = 340,
 		KEY_LEFT_CONTROL,
 		KEY_LEFT_ALT,
 		KEY_LEFT_SUPER,
 		KEY_RIGHT_SHIFT,
 		KEY_RIGHT_CONTROL,
 		KEY_RIGHT_ALT,
 		KEY_RIGHT_SUPER,
 		KEY_MENU,
 		KEY_LAST = KEY_MENU
	};

	enum KeyAction
	{
		KEY_PRESS = GLFW_PRESS,
		KEY_RELEASE = GLFW_RELEASE,
		KEY_REPEAT = GLFW_REPEAT
	};

	enum MouseButton
	{
		LEFT_BUTTON = GLFW_MOUSE_BUTTON_LEFT,
		RIGHT_BUTTON = GLFW_MOUSE_BUTTON_RIGHT
	};

	enum MouseAction
	{
		MOUSE_PRESS = GLFW_PRESS,
		MOUSE_RELEASE = GLFW_RELEASE
	};

	//static class GLEvent to pass func ptr to glfw initializing func
	class GLEvent
	{
	public:
		static void setViewport(GLViewport* view);
		//
		static void onGLError(int errorID, const char* errorDesc);
		//
		static void onKeyCall(GLFWwindow* wnd, int keyCode, int scanCode, int action, int mode);
		static void onScrollCall(GLFWwindow* wnd, double x, double y);
		static void onMousePressCall(GLFWwindow* wnd, int btn, int action, int modify);
		static void onMouseMoveCall(GLFWwindow* wnd, double x, double y);
		//
		static void keyDidPressed();
		//
		static int getKeyState(const int& keycode);
		static int getMouseState(const int& btn);

	private:
		//at present, a application can only run one window 
		static GLViewport* _viewport;
		//refer to 120 KeyCode declare on the top, pressed -> true
		static bool _keyState[120];
	};



	class Event
	{
	public:
	protected:
	private:
	};

}

#endif