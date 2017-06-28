/********************************************************************
	created:	2017/01/16
	filename: 	Macros.h
	file ext:	h
	author:		Yohiro
	
	purpose:	引擎中常用的宏定义
*********************************************************************/
#ifndef MACROS_H
#define MACROS_H

#include <string>
#include "windows.h"

#define DEBUG_BREAK			__asm { int 3 }

inline void _error(std::string string, int line, char* file)
{
	char temp[512];
	OutputDebugStringA("\n//----------------------------------------------------------------------------\n");
	sprintf_s(temp, 512, "// ERROR\n");
	OutputDebugStringA(temp);
	sprintf_s(temp, 512, "// Line %d\n", line);
	OutputDebugStringA(temp);
	sprintf_s(temp, 512, "// File %s\n", file);
	OutputDebugStringA(temp);
	sprintf_s(temp, 512, "// Message: %s\n", string.c_str());
	OutputDebugStringA(temp);
	OutputDebugStringA("//----------------------------------------------------------------------------\n\n");
	DEBUG_BREAK;
}

inline void _assert(void* cond, std::string string, int line, char* file)
{
	if (!cond)
		_error(string, line, file);
}

inline void _assert(bool cond, std::string string, int line, char* file)
{
	if (!cond)
		_error(string, line, file);
}

inline void _assert(bool cond)
{
	if (!cond)
		_error("General assertion", 0, "");
}

//
#define UCExport					__declspec(dllexport)		//
#define UCImport					__declspec(dllimport)		//
#define UCFastcall					__fastcall					//
#define UCInline					__inline					//
#define UCForceInline				__forceinline				//
#define UCAlign16					__declspec(align(16))		//
#define UCNaked						__declspec(naked)			//

#define NS_UNICORN using namespace Unicorn
#define UC_BEGIN   namespace Unicorn {
#define UC_END	   }

//
#ifdef UC_DLL_IMPORT
	#define UC_DLL UCImport
#else
	#ifdef UC_DLL_EXPORT
		#define  UC_DLL UCExport
	#else
		#define  UC_DLL
	#endif
#endif	

//memory manage macros
#define UCSafeFree( ptr )       { if( ptr != NULL ) { free( ptr ); ptr = NULL;} }
#define UCSafeDelete( ptr )     { if( ptr != NULL ) { delete ptr; ptr = NULL;} }
#define UCSafeDeleteArr( arr )  { if( arr != NULL ) { delete[] arr; arr = NULL;} }

//set debug mode or release
#ifdef DEBUG_MODE
	#define UCFree( ptr )			UCSafeFree( ptr )
	#define UCDelete( ptr )			UCSafeDelete( ptr )
	#define UCDeleteArr( arr )		UCSafeDeleteArr( arr )
#else
	#define UCFree( ptr )			{ free( ptr ); }
	#define UCDelete( ptr )			{ delete ptr; }
	#define UCDeleteArray( arr )	{ delete [] arr; }
#endif

//#define UC_ASSERT(cdt, msg)
#define UC_BREAK( cdt )        do{  if(!(cdt)) break;  }while(false)

//convenient macros in program
#define MAX(a, b)  ( a> b? : a: b)
#define MIN(a, b)  ( a< b? : a: b)

#define LOG( format, ... )		printf( format, __VA_ARGS__ ) 

#define GEN_SGET_FUNC( varType, varName, funcName)\
public: virtual varType get##funcName(void) const { return varName; }\
public: virtual void set##funcName(const varType& var){ varName = var; }\

#define GEN_SGET_FUNC_INLINE( varType, varName, funcName)\
public: virtual __inline varType get##funcName(void) const { return varName; }\
public: virtual __inline void set##funcName(const varType& var){ varName = var; }\

#define GEN_SGET_FUNC_INLINE_UNCON( varType, varName, funcName)\
public: virtual __inline varType get##funcName(void) const { return varName; }\
public: virtual __inline void set##funcName(varType var){ varName = var; }\


#define GEN_FUNC( varType, varName, funcName)							\
public: virtual varType get##funcName(void) const { return varName; }   \
public: virtual void set##funcName(const varType& var){ varName = var; }\

#define MAKE_CALLBACK(_func_) std::bind(_func_)

#define CLAMP( var, down, top)\
	    if (var < down)\
			var = down;\
		else if (var > top)\
			var = top; \


#define asm_cast(var,addr)  \
{                           \
	__asm{                  \
	mov var, offset addr    \
	}                       \
}

#define Log( _format_, ... )               \
{							               \
	char msg[128];			               \
	sprintf(msg, _format_, ##__VA_ARGS__); \
	Logger::log(msg);		               \
}							               \

#define MATRIX_VALUE_PTR( _mat_ )  glm::value_ptr( _mat_ )
#define RADIANS( _degree_ ) 	_degree_ * 0.01745329251994329576923690768489
#define PI 3.1415926
#define MEM_SET_ZERO(a) memset(a, 0, sizeof(a))

#define INVALID_OGL_VALUE 0xffffffff
#define INVALID_UNIFORM_LOCATION -1

#define MAX_PARTICLE_COUNT 10000

//map from unicorn engine to gl
#define MAX_TEXTURE_TARGET_COUNT		32
#define COLOR_TEXTURE_UNIT              GL_TEXTURE0
#define COLOR_TEXTURE_UNIT_INDEX        0
#define SHADOW_TEXTURE_UNIT             GL_TEXTURE1
#define SHADOW_TEXTURE_UNIT_INDEX       1
#define NORMAL_TEXTURE_UNIT             GL_TEXTURE2
#define NORMAL_TEXTURE_UNIT_INDEX       2
#define RANDOM_TEXTURE_UNIT             GL_TEXTURE3
#define RANDOM_TEXTURE_UNIT_INDEX       3
#define DISPLACEMENT_TEXTURE_UNIT       GL_TEXTURE4
#define DISPLACEMENT_TEXTURE_UNIT_INDEX 4
#define MOTION_TEXTURE_UNIT             GL_TEXTURE5
#define MOTION_TEXTURE_UNIT_INDEX       5
#define CASCACDE_SHADOW_TEXTURE_UNIT0       SHADOW_TEXTURE_UNIT
#define CASCACDE_SHADOW_TEXTURE_UNIT0_INDEX SHADOW_TEXTURE_UNIT_INDEX
#define CASCACDE_SHADOW_TEXTURE_UNIT1       GL_TEXTURE6
#define CASCACDE_SHADOW_TEXTURE_UNIT1_INDEX 6
#define CASCACDE_SHADOW_TEXTURE_UNIT2       GL_TEXTURE7
#define CASCACDE_SHADOW_TEXTURE_UNIT2_INDEX 7

#define MAX_RAND 0x7fff

#define GLExitIfError															\
{																				\
	GLenum Error = glGetError();												\
																				\
	if (Error != GL_NO_ERROR) {											        \
		printf("OpenGL error in %s:%d: 0x%x\n", __FILE__, __LINE__, Error);     \
		exit(0); }                                                              \
}                                                                               \


#define GLCheckError() (glGetError() == GL_NO_ERROR)
#define UC_ASSERT(COND, MEX)		(_assert(COND, MEX, __LINE__, __FILE__))
#define UC_ERROR(MEX)				(_error(MEX, __LINE__, __FILE__))


#endif
