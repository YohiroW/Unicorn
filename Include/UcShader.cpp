#include "UcShader.h"
#include "UcLogger.h"
NS_UNICORN;

Shader::Shader()
{

}

Shader::~Shader()
{

}

bool Shader::initialize(const char* shaderPath, ShaderType shaderType)
{
	_shaderHandler = _compileShader(shaderPath, shaderType);
	if (_shaderHandler == LINK_FAILURE)
	{
		return false;
	}
	return true;
}

bool Shader::initializeWithCode(const char* shaderCode, ShaderType shaderType)
{
	_shaderHandler = _compileShaderCode(shaderCode, shaderType);
	if (_shaderHandler == LINK_FAILURE)
	{
		return false;
	}
	return true;
}

char* Shader::_readShaderFromFile(const char* filePath) const
{
	FILE* shaderFile = fopen(filePath, "r");
	if (!shaderFile)
	{
		//log error
		//can not find valid shader at path => shaderFile
		Log("ERROR: ERROR FILE PATH AT %s\n", filePath);
		return NULL;
	}

	fseek(shaderFile, 0, SEEK_END);
	size_t size = ftell(shaderFile);

	char* shaderCode = new char[size];
	memset(shaderCode, 0, size);

	rewind(shaderFile);
	fread(shaderCode, size, 1, shaderFile);
	fclose(shaderFile);

	return shaderCode;
}

ShaderID Shader::_compileShader(const char* filePath, ShaderType shaderType) const
{
	char* code = _readShaderFromFile(filePath);
	if (!code)
	{
		Log("ERROR: ERROR FILE PATH AT %s\n", filePath);
		//log compile failed
		return LINK_FAILURE;
	}
	
	GLint isCompileSuccess;
	ShaderID shaderHandler = glCreateShader(shaderType);
	glShaderSource(shaderHandler,1,&code,NULL);
	glCompileShader(shaderHandler);

	//
	GLchar logMsg[MAX_BUFFER_SIZE];
	glGetShaderiv(shaderHandler, GL_COMPILE_STATUS, &isCompileSuccess);
	if (!isCompileSuccess)
	{
		glGetShaderInfoLog(shaderHandler,MAX_BUFFER_SIZE,NULL, logMsg);
		Log("ERROR: SHADER %s LINK FAILED: %s\n",filePath, logMsg);
		return LINK_FAILURE;
	}

	UCSafeDelete(code);
	return shaderHandler;
}


ShaderID Shader::_compileShaderCode(const char* code, ShaderType shaderType) const
{
	if (!code)
	{
		Log("ERROR: SHADER CODE AT CAN NOT BE NIL! \n");
		//log compile failed
		return LINK_FAILURE;
	}

	GLint isCompileSuccess;
	ShaderID shaderHandler = glCreateShader(shaderType);
	glShaderSource(shaderHandler, 1, &code, NULL);
	glCompileShader(shaderHandler);

	//
	GLchar logMsg[MAX_BUFFER_SIZE];
	glGetShaderiv(shaderHandler, GL_COMPILE_STATUS, &isCompileSuccess);
	if (!isCompileSuccess)
	{
		glGetShaderInfoLog(shaderHandler, MAX_BUFFER_SIZE, NULL, logMsg);
		Log("ERROR: SHADER LINK FAILED: %s\n", logMsg);
		return LINK_FAILURE;
	}

	UCSafeDelete(code);
	return shaderHandler;
}

ShaderID Shader::getShaderHandler() const
{
	return _shaderHandler;
}

void Shader::destroy()
{

}
