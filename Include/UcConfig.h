#ifndef CONFIG_H
#define CONFIG_H
//

#include <GLFW/glfw3.h>
#include <functional>

#define LINK_FAILURE -1


typedef unsigned long ucDword;
typedef unsigned char ucByte;
typedef char* cstr;
typedef GLuint ShaderID;
typedef GLuint ShaderProgramID;
typedef GLuint TextureID;
typedef unsigned int uint;
typedef unsigned short ucshort;

typedef std::function< void(GLFWwindow*, int, int, int, int)> Keyboard_Callback;
typedef std::function< void(GLFWwindow*, int, int, int)> MouseClick_Callback;
typedef std::function< void(GLFWwindow*, double, double)>     MouseMove_Callback;
typedef std::function< void(GLFWwindow*, double, double)>      Scroll_Callback;

//
typedef void (* KeyCallbackPtr)(GLFWwindow*, int, int, int, int);
typedef void (* MouseClickCallbackPtr)(GLFWwindow*, int, int, int);
typedef void (* MouseMoveCallbackPtr)(GLFWwindow*, double, double);
typedef void(*ScrollCallbackPtr)(GLFWwindow*, double, double);
//
const double UC_PI = 3.1415926;
//default maxium fps
const int FRAME_PER_SEC = 60;
//
const unsigned int MAX_FRAME_SKIP = 10;
//
const short MAX_BUFFER_SIZE = 512;



#endif
