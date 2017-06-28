#ifndef _UC_BUFFER_H_
#define _UC_BUFFER_H_
//
#include "UcReference.h"
#include "UcConfig.h"
#include "UcObject.h"
//
namespace Unicorn
{
	class Buffer: public Object
	{
	public:
		//
		virtual ~Buffer();
		//
		enum BufferUsage
		{
			BU_STATIC,
			BU_DYNAMIC,
			BU_RENDERTARGET,
			BU_DEPTH_STENCIL,
			BU_TEXTURE,
			BU_QUANTITY
		};
		//
		enum BufferLockMode
		{
			BLM_READ_ONLY,
			BLM_WRITE_ONLY,
			BLM_READ_WRITE,
			BLM_QUANTITY
		};

		inline void setElementCount(int numElements){
			_numElements = numElements;
		}

		inline int getElementNum() const{
			return _numElements;
		}

		inline BufferUsage getUsage() const{
			return _usage;
		}

		inline uint getNumBytes() const{
			return _numBytes;
		}

		inline int getElemSize() const{
			return _elemSize;
		}

	protected:
		Buffer();
		Buffer(int numElements,int elemSize,BufferUsage usage);
		//
		int _numElements;
		int _elemSize;
		BufferUsage _usage;
		uint _numBytes;
		char* _buffer;
	};
}

#endif