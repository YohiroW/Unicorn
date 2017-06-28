#ifndef _UC_GLBUFFER_H_
#define _UC_GLBUFFER_H_
//
#include "UcMacros.h"

namespace Unicorn
{
	enum GLBufferType
	{
		VERTEX_ARRAY_BUFFER,
		VERTEX_OBJECT_BUFFER,
		INDEX_OBJECT_BUFFER,
		FRAME_BUFFER,
		RENDER_BUFFER
	};

	class GLBuffer
	{
	public:

		virtual void generate(const int& count = 1) = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;	


	protected:

	};
}


#endif