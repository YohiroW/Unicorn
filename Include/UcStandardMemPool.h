#ifndef _UC_STANDARDMEMPOOL_H_
#define _UC_STANDARDMEMPOOL_H_
//
#include "UcObject.h"
#include "UcMemPool.h"

namespace Unicorn
{
	class StandardMemPool: public MemPool
	{
	public:
		// Methods
		//-----------------------------------------	
		inline void* allocate(ucDword size);
		inline void free(void* ptr);
		inline bool integrityCheck() const;
		inline void dumpToFile(const std::string& fileName, const ucDword itemsPerLine) const;

		// Static
		//-----------------------------------------	
		static const ucByte s_minFreeBlockSize = 16;

	private:
		friend class MemoryPoolManager;

		// Ctors/Dtor
		//-----------------------------------------
		StandardMemPool(ucDword sizeInucBytes, bool boundCheck)
		{
			//
			if (boundCheck) m_boundsCheck = 1;

			//
			m_poolMemory = ::new unsigned char[sizeInucBytes];

			m_freePoolSize = sizeInucBytes - sizeof(Chunk);
			m_totalPoolSize = sizeInucBytes;

			//
			if (m_trashOnCreation)
				memset(m_poolMemory, s_trashOnCreation, sizeInucBytes);

			//
			if (m_boundsCheck)
			{
				m_freePoolSize -= s_boundsCheckSize * 2;

				Chunk freeChunk(sizeInucBytes - sizeof(Chunk)-2 * s_boundsCheckSize);
				freeChunk.write(m_poolMemory + s_boundsCheckSize);
				memcpy(m_poolMemory, s_startBound, s_boundsCheckSize);
				memcpy(m_poolMemory + sizeInucBytes - s_boundsCheckSize, s_endBound, s_boundsCheckSize);
			}
			else
			{
				Chunk freeChunk(sizeInucBytes - sizeof(Chunk));
				freeChunk.write(m_poolMemory);
			}
		}

		~StandardMemPool()
		{}

	private:
		// inner structure
		class Chunk
		{
		public:
			Chunk(ucDword userDataSize) :
				m_next(NULL), 
				m_prev(NULL), 
				m_userdataSize(userDataSize), 
				m_free(true)
			{};

			//
			void write(void* dest){ memcpy(dest, this, sizeof(Chunk)); }
			void read(void* src){ memcpy(this, src, sizeof(Chunk)); }

			Chunk*  m_next;
			Chunk*  m_prev;
			ucDword   m_userdataSize;
			bool    m_free;
		};

		// attributes
		ucByte*		        m_poolMemory;
	};
	#include "UcStandardMemPool.inl"
}

#endif