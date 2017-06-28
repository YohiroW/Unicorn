#ifndef _UC_VERTEXBUF_H_
#define _UC_VERTEXBUF_H_
//
#include "UcBuffer.h"
//

namespace Unicorn
{
	class VertexBuffer : public Buffer
	{
	public:
		//
		VertexBuffer(int vertexNum, int vertexSize, BufferUsage usage = BU_STATIC);
		virtual ~VertexBuffer();
		//
		inline char* getBufferData() const{
			return _buffer;
		}
	};
}

#endif