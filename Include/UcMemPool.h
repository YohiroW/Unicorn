#ifndef MEMPOOL_H
#define MEMPOOL_H
//
#include <list>
#include <string>
#include "UcObject.h"

#define TRASH_POOLS 1


namespace Unicorn
{

	class MemPool
	{
	public:
		// Static
		//-----------------------------------------	
		static const ucByte   s_trashOnCreation = 0xCC;
		static const ucByte   s_trashOnAllocSignature = 0xAB;
		static const ucByte   s_trashOnFreeSignature = 0xFE;
		static const ucByte   s_boundsCheckSize = 16;
		static const ucByte   s_startBound[s_boundsCheckSize];
		static const ucByte   s_endBound[s_boundsCheckSize];


		//-----------------------------------------	
		inline virtual void*    allocate(ucDword size) = 0;
		inline virtual void     free(void* ptr) = 0;
		inline virtual bool     integrityCheck() const = 0;
		inline virtual void     dumpToFile(const std::string& fileName, const ucDword itemsPerLine) const = 0;

		inline ucDword  getFreePoolSize() const { return m_freePoolSize; }
		inline ucDword  getTotalPoolSize() const { return m_totalPoolSize; }
		inline bool hasBoundsCheckOn() const { return m_boundsCheck; }

	protected:
		// Ctor/Dtor
		MemPool() : m_totalPoolSize(0), m_freePoolSize(0), m_trashOnCreation(TRASH_POOLS), m_trashOnAlloc(TRASH_POOLS), m_trashOnFree(TRASH_POOLS), m_boundsCheck(0) {};
		virtual ~MemPool(){};

		// Variables
		ucDword       m_totalPoolSize;
		ucDword       m_freePoolSize;

		// Bitfield
		unsigned    m_trashOnCreation : 1;
		unsigned    m_trashOnAlloc : 1;
		unsigned    m_trashOnFree : 1;
		unsigned    m_boundsCheck : 1;
	};

}
#endif // MEMPOOL_H