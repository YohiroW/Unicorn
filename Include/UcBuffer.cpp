#include "UcBuffer.h"
NS_UNICORN;

Buffer::Buffer()
:
_numElements(0),
_elemSize(0),
_usage(BufferUsage::BU_QUANTITY),
_numBytes(0),
_buffer(0)
{

}

Buffer::Buffer(int numElements, int elemSize, BufferUsage usage)
:
_numElements(numElements),
_elemSize(elemSize),
_usage(usage),
_numBytes(numElements* elemSize)
{
	//assert(_numElements >0, "");
	//assert(_elemSize > 0, "");
	_buffer = new char[_numBytes];
}

Buffer::~Buffer()
{
	UCSafeDeleteArr(_buffer);
}

