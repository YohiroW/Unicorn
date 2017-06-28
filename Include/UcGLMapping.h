#ifndef _UC_GLMAPPING_H_
#define _UC_GLMAPPING_H_
#include <gl/glew.h>
#include "UcConfig.h"
#include "UcBuffer.h"

//
namespace Unicorn
{
	GLuint GLBufferUsage[Buffer::BU_QUANTITY] =
	{
		GL_STATIC_DRAW,     // BU_STATIC
		GL_DYNAMIC_DRAW,    // BU_DYNAMIC
		GL_DYNAMIC_DRAW,    // BU_RENDERTARGET
		GL_DYNAMIC_DRAW,    // BU_DEPTHSTENCIL
		GL_DYNAMIC_DRAW     // BU_TEXTURE
	};

	GLuint GLBufferLockMode[Buffer::BLM_QUANTITY] =
	{
		GL_READ_ONLY,   // BL_READ_ONLY
		GL_WRITE_ONLY,  // BL_WRITE_ONLY
		GL_READ_WRITE   // BL_READ_WRITE
	};
}

#endif