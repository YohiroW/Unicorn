#include "UcMemPool.h"
#include "UcMemPoolMgr.h"
NS_UNICORN;

const ucByte  MemPool::s_startBound[16] = { '[', 'B', 'l', 'o', 'c', 'k', '.', '.', '.', '.', 'S', 't', 'a', 'r', 't', ']' };
const ucByte  MemPool::s_endBound[16] = { '[', 'B', 'l', 'o', 'c', 'k', '.', '.', '.', '.', '.', '.', 'E', 'n', 'd', ']' };

