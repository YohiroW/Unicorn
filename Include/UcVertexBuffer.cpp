#include "UcVertexBuffer.h"
NS_UNICORN;

VertexBuffer::VertexBuffer(int vertexNum, int vertexSize, BufferUsage usage /* = BU_STATIC */)
:Buffer(vertexNum,vertexSize,usage)
{
}

VertexBuffer::~VertexBuffer()
{
	UCSafeDeleteArr(_buffer);
}
