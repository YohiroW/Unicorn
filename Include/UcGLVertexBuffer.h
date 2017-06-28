#ifndef _UC_VERTEX_BUFFER_H_
#define _UC_VERTEX_BUFFER_H_
//
#include <gl/glew.h>
#include <hash_map>
#include "UcRenderer.h"
#include "UcVertexBuffer.h"
#include "UcConfig.h"
//
namespace Unicorn
{
	class GLVertexBuffer
	{
	public:
		//renderer passed into without using
		GLVertexBuffer(Renderer* renderer, const VertexBuffer* vbuf);
		~GLVertexBuffer();
		//
		void enable(Renderer* renderer, uint vtxSize, uint streamIndex, uint offset);
		void disable(Renderer* renderer, uint streamIndex);
		//
		void* lock(Buffer::BufferLockMode lockMode);
		void unlock();

	private:
		GLuint _buffer;
	};
}


#endif