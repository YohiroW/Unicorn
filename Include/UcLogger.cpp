#include "UcLogger.h"
NS_UNICORN;

void Logger::log(const std::string& str)
{
	OutputDebugString(str.c_str());
}

