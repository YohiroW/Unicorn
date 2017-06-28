#include "UcMemPoolMgr.h"
NS_UNICORN;

const char* const	MemPoolMgr::c_poolsFileXML = "./pools.xml";

MemPoolMgr::MemPoolMgr(const char* const poolsFileXML)
{
}

bool MemPoolMgr::isValidPoolType(const char* poolType) const
{
	if (strcmp(poolType, "pool") == 0) return true;
	return false;
}