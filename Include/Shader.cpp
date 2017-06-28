#include "Shader.h"


Shader::Shader(const char* vertexShader,const char* fragmentShader)
{
	//
	string vertexCode;
	string fragmentCode;
	//
	try
	{
		ifstream vShaderFile;
		ifstream fShaderFile;
		//
		stringstream vShaderStr,fShaderStr;
		//
		vShaderFile.open(vertexShader);
		if(!vShaderFile)
		{
			printf("ERROR: CAN NOT FIND FILE AT %s",vShaderFile);
		}
		fShaderFile.open(fragmentShader);
		if(!fShaderFile)
		{
			printf("ERROR: CAN NOT FIND FILE AT %s",fShaderFile);
		}
		vShaderStr << vShaderFile.rdbuf();
		fShaderStr << fShaderFile.rdbuf();
		
		vShaderFile.close();
		fShaderFile.close();
		//
		vertexCode = vShaderStr.str();
		fragmentCode = fShaderStr.str();
	}
	catch (exception e)
	{
		printf("ERROR: FAILED TO READ SHADER FILES\n");
	}

	const char* vertexCodeSource = vertexCode.c_str();
	const char* fragmentCodeSource = fragmentCode.c_str();

	//create shader by what we read
	GLuint vertex,fragment;
	GLchar logInfo[512];
	GLint  isSuccess;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex,1,&vertexCodeSource,NULL);
	glCompileShader(vertex);

	//check shader status
	glGetShaderiv(vertex,GL_COMPILE_STATUS,&isSuccess);
	if(!isSuccess)
	{
		glGetShaderInfoLog(vertex, 512, NULL, logInfo);
		printf("ERROR:: VERTEX SHADER COMPILE FAILED\n %s",logInfo);
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment,1,&fragmentCodeSource,NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment,GL_COMPILE_STATUS,&isSuccess);
	if(!isSuccess)
	{
		glGetShaderInfoLog(fragment, 512, NULL, logInfo);
		printf("ERROR:: FRAGMENT SHADER COMPILE FAILED\n %s",logInfo );
	}

	_program = glCreateProgram();
	glAttachShader(_program,vertex);
	glAttachShader(_program,fragment);
	glLinkProgram(_program);
	glGetProgramiv(_program,GL_LINK_STATUS,&isSuccess);
	if(!isSuccess)
	{
		glGetProgramInfoLog(_program, 512, NULL, logInfo);
		printf("ERROR: SHADER PROGRAM LINK FAILED\n %s",logInfo);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::apply()
{
	glUseProgram(_program);

}

void Shader::addUniform(GLuint attrLocation,const char* attr)
{
	GLint loc = glGetUniformLocation(_program,attr);

}

Shader::~Shader(void)
{
}
