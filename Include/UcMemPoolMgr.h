#ifndef MEMPOOLMGR_H
#define MEMPOOLMGR_H
//
#include <vector>
#include "UcMacros.h"
#include "UcMemPool.h"

namespace Unicorn
{
	class MemPoolMgr : public Object
	{
	public:
		//
		static const char* const	c_poolsFileXML;
		static MemPoolMgr&	it() 
		{
			static MemPoolMgr instance(c_poolsFileXML); 
			return instance; 
		};

		//-----------------------------------------	
		MemPool* getPool(const char* const name)
		{
			std::map<std::string, MemPool*>::iterator iter = m_pool.find(name);
			if (iter != m_pool.end())	
				return iter->second;
			else
			{
				UC_ERROR("Pool " + std::string(name) + " not found.");
				return NULL;
			}
		}

		void dumpAllPools() const
		{
			dumpAllPools("");
		}

		void dumpAllPools(const std::string& prefix) const
		{
			std::map<std::string, MemPool*>::const_iterator iter = m_pool.begin();
			for (iter; iter != m_pool.end(); ++iter)
			{
				iter->second->dumpToFile(prefix + std::string(iter->first) + ".txt", 4);
			}
		}

		void dumpPool(const std::string& prefix, const MemPool* pool) const
		{
			std::map<std::string, MemPool*>::const_iterator iter = m_pool.begin();
			for (iter; iter != m_pool.end(); ++iter)
			{
				if (pool == iter->second)
				{
					iter->second->dumpToFile(prefix + std::string(iter->first) + ".txt", 4);
				}
			}
		}

	private:
	
		//	
		MemPoolMgr(const char* const poolsFileXML);

		bool isValidPoolType(const char* poolType) const;
		MemPool* allocateByPoolType(const char* poolType) const;

		// Attributes
		//-----------------------------------------
		std::map<std::string, MemPool*>	m_pool;
	};

}
#endif // MEMPOOL_H