#ifndef UC_ALLOCATOR
#define UC_ALLOCATOR
//


#include "UcObject.h"
#include "UcMemPoolMgr.h"

namespace Unicorn
{

	inline void* operator new(size_t size, MemPool& pool)
	{
		void* ptr = pool.allocate(size);
		UC_ASSERT(ptr, "memory is not enough of this pool");
		return ptr;
	}


	inline void operator delete(void* ptr, MemPool& pool)
	{
		pool.free(ptr);
	}


	template<class T>
	void __delete__(T* ptr, MemPool& pool)
	{
		if (ptr) {
			ptr->~T();
			pool.free(ptr);
		}
	}


#undef      DELETE

#define		NEW(memoryPool)	 new(*memoryPool)
#define		DELETE(memoryPool, ptr) 	__delete__(ptr, *memoryPool)
#define		POOL(name)	(MemPoolMagr::it().getPool(name))


}
#endif