#pragma once
#include <vector>
#include "UcConfig.h"
#include "UcObject.h"

namespace Unicorn
{

class Package : public Object
{
public:
	struct packageProp
	{
		unsigned int fileCount;
		int packHeadSize;
	};

	struct fileProp
	{
		char fileName[20];
		long offSetInFile;
		long fileSize;
	};

public:
	Package(void);
	~Package(void);

	//
	bool initialize(const char* packName);
	//add a file into pack
	void addFile(const char* file);
	bool makePackage();
	//unpack into local document
	bool unpack(const char* fileName);

private:
	unsigned int _count;
	std::string  _packName;
	std::vector<const char*> _sourceFileSet;
};

}
