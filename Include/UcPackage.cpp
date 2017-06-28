#include "UcPackage.h"
using namespace Unicorn;


Package::Package(void)
{
}


Package::~Package(void)
{
}

void Package::addFile(const char* file)
{
	_sourceFileSet.push_back(file);
	_count++;
}

bool Package::initialize(const char* packName)
{
	_packName = packName;
	_count = 0;

	return true;
}

bool Package::makePackage()
{
	FILE *dstPack, *sourceFile;
	dstPack = fopen(_packName.c_str(), "wb");

	packageProp packInfo;
	packInfo.fileCount = _count;
	packInfo.packHeadSize = sizeof(packageProp)+_count* sizeof(fileProp);
	//
	fileProp* fileInfo = new fileProp[_count];
	long offset = packInfo.packHeadSize;

	fwrite(&packInfo, sizeof(packageProp), 1, dstPack);
	for (int i = 0; i < _count; ++i)
	{
		sourceFile = fopen(_sourceFileSet[i], "rb");
		if (!sourceFile)
		{
			return false;
		}
		fseek(sourceFile, 0, SEEK_END);
		strcpy(fileInfo[i].fileName, _sourceFileSet[i]);
		//get file length
		fileInfo[i].fileSize = ftell(sourceFile);
		fileInfo[i].offSetInFile = offset;
		//
		offset += fileInfo[i].fileSize;
		fwrite(&fileInfo[i], sizeof(fileProp), 1, dstPack);
		fclose(sourceFile);
	}

	for (int i = 0; i < _count; ++i)
	{
		sourceFile = fopen(_sourceFileSet[i], "rb");
		//write to pack
		int offSet = fileInfo[i].offSetInFile;
		fseek(dstPack, offSet, SEEK_SET);
		int ptrpos = ftell(dstPack);

		cstr buffer = new char[fileInfo[i].fileSize];
		fread(buffer, fileInfo[i].fileSize, 1, sourceFile);
		fwrite(buffer, fileInfo[i].fileSize, 1, dstPack);

		ptrpos = ftell(dstPack);

		fclose(sourceFile);
		delete buffer;
	}

	fclose(dstPack);
	delete fileInfo;

	return true;
}

bool Package::unpack(const char* packName)
{
	FILE* pack = fopen(packName, "rb");
	if (!pack)
	{
		return false;
	}

	packageProp packInfo;
	fread(&packInfo, sizeof(packageProp), 1, pack);

	fileProp* fileInfo = new fileProp[packInfo.fileCount];
	for (int i = 0; i < packInfo.fileCount; ++i)
	{
		fread(&(fileInfo[i]), sizeof(fileProp), 1, pack);
	}

	FILE* dst = 0;
	long ptrPos = 0;
	for (int i = 0; i < packInfo.fileCount; ++i)
	{
		dst = fopen(fileInfo[i].fileName, "wb");

		//relocate file pointer to head of no.i 
		int offSet = fileInfo[i].offSetInFile;
		fseek(pack, offSet, SEEK_SET);
		long ptrpos = ftell(pack);
		cstr buffer = new char[fileInfo[i].fileSize];

		fread(buffer, fileInfo[i].fileSize, 1, pack);
		fwrite(buffer, fileInfo[i].fileSize, 1, dst);

		ptrpos = ftell(pack);

		delete buffer;
		fclose(dst);
	}

	fclose(pack);
	delete fileInfo;

	return true;
}