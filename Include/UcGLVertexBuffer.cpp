#include "UcGLVertexBuffer.h"
#include "UcGLMapping.h"
NS_UNICORN;

GLVertexBuffer::GLVertexBuffer(Renderer* renderer, const VertexBuffer* vbuf)
{
	//
	glGenBuffers(1,&_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	//
	glBufferData(GL_ARRAY_BUFFER, vbuf->getNumBytes(),0, GLBufferUsage[vbuf->getUsage()]);
	//
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//
	void* data = lock(Buffer::BLM_WRITE_ONLY);
	memcpy(data, vbuf->getBufferData(), vbuf->getNumBytes());

	unlock();
}

GLVertexBuffer::~GLVertexBuffer()
{
	glDeleteBuffers(1, &_buffer);
}

void GLVertexBuffer::enable(Renderer* renderer, uint vtxSize, uint streamIndex, uint offset)
{
	//
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
}

void GLVertexBuffer::disable(Renderer* renderer, uint streamIndex)
{
	//
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void* GLVertexBuffer::lock(Buffer::BufferLockMode lockMode)
{
	//
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	//
	GLvoid* videoMem = glMapBuffer(GL_ARRAY_BUFFER, GLBufferLockMode[lockMode]);
	//
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return videoMem;
}

void GLVertexBuffer::unlock()
{
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
