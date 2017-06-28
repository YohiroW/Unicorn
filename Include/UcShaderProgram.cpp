#include "UcShaderProgram.h"
#include "UcShaderMgr.h"
#include "UcLogger.h"
NS_UNICORN;

ShaderProgram::ShaderProgram():
_programHandler(0),
_vertexShader(NULL),
_fragmentShader(NULL),
_geometryShader(NULL)
{
}

ShaderProgram::~ShaderProgram()
{
}

bool ShaderProgram::initializeWithCode(const char* vertexShader, const char* fragShader, const char* geometryShader /* = NULL */)
{
	//
	_vertexShader = ShaderMgr::getInstance()->createShaderWithCode(vertexShader,Shader::ShaderType::VERTEX);
	_fragmentShader = ShaderMgr::getInstance()->createShaderWithCode(fragShader, Shader::ShaderType::FRAGMENT);
	
	if (geometryShader)
	{
		_geometryShader = ShaderMgr::getInstance()->createShaderWithCode(geometryShader, Shader::ShaderType::GEOMETRY);
		_programHandler = _linkShaderProgram(_vertexShader, _fragmentShader, _geometryShader);
	}
	else
	{
		_programHandler = _linkShaderProgram(_vertexShader, _fragmentShader);
	}
	//
	if (_programHandler == LINK_FAILURE)
		return false;

	return true;
}

bool ShaderProgram::initialize(Shader* vertexShader, Shader* fragShader, Shader* geometryShader /* = NULL */)
{
	_vertexShader = vertexShader;
	_fragmentShader = fragShader;
	
	if (geometryShader)
	{
		_geometryShader = geometryShader;
		_programHandler = _linkShaderProgram(vertexShader, fragShader, geometryShader);
	}
	else
	{
		_programHandler = _linkShaderProgram(vertexShader, fragShader);
	}
	//
	if (_programHandler == LINK_FAILURE)
		return false;

	return true;
}

ShaderProgramID ShaderProgram::_linkShaderProgram(Shader* vertexShader, Shader* fragmentShader) const
{
	if (!vertexShader || !fragmentShader)
	{
		//log error
		return LINK_FAILURE;
	}

	ShaderProgramID programHandler = glCreateProgram();
	glAttachShader(programHandler, vertexShader->getShaderHandler());
	glAttachShader(programHandler, fragmentShader->getShaderHandler());
	glLinkProgram(programHandler);
	
	GLint isLinked;
	char logInfo[MAX_BUFFER_SIZE];
	glGetProgramiv(programHandler,GL_LINK_STATUS, & isLinked);
	if (!isLinked)
	{
		glGetProgramInfoLog(programHandler,MAX_BUFFER_SIZE,NULL,logInfo);
		Log("ERROR: SHADER PROGRAM LINK FAILED, SEE DETAIS: %s\n",logInfo);
		return LINK_FAILURE;
	}

	glDeleteShader(vertexShader->getShaderHandler());
	glDeleteShader(fragmentShader->getShaderHandler());

	return programHandler;
}

ShaderProgramID ShaderProgram::_linkShaderProgram(Shader* vertexShader, Shader* fragmentShader, Shader* geometryShader) const
{
	if (!vertexShader || !fragmentShader || !geometryShader)
	{
		//log error
		return LINK_FAILURE;
	}

	ShaderProgramID programHandler = glCreateProgram();
	glAttachShader(programHandler, vertexShader->getShaderHandler());
	glAttachShader(programHandler, fragmentShader->getShaderHandler());
	glAttachShader(programHandler, geometryShader->getShaderHandler());
	glLinkProgram(programHandler);

	GLint isLinked;
	char logInfo[MAX_BUFFER_SIZE];
	glGetProgramiv(programHandler, GL_LINK_STATUS, &isLinked);
	if (!isLinked)
	{
		glGetProgramInfoLog(programHandler, MAX_BUFFER_SIZE, NULL, logInfo);
		Log("ERROR: SHADER PROGRAM LINK FAILED, SEE DETAIS: %s\n", logInfo);
		return LINK_FAILURE;
	}

	glDeleteShader(vertexShader->getShaderHandler());
	glDeleteShader(fragmentShader->getShaderHandler());
	glDeleteShader(geometryShader->getShaderHandler());

	return programHandler;
}

ShaderProgramID ShaderProgram::getShaderProgramID() const
{
	return _programHandler;
}

void ShaderProgram::apply()
{
	glUseProgram(_programHandler);
}

void ShaderProgram::setVector2(const char* locName, const Vector2& vec2, bool isApplied)
{
	if (!isApplied)
		this->apply();
	glUniform2f(glGetUniformLocation(this->_programHandler, locName), vec2.x, vec2.y);
}

void ShaderProgram::setVector2(GLint loc, const Vector2& vec2, bool isApplied /*= false*/)
{
	if (!isApplied)
		this->apply();

	glUniform2f(loc, vec2.x, vec2.y);
}

void ShaderProgram::setVector3(GLint loc, const Vector3& vec3, bool isApplied /*= false*/)
{
	if (!isApplied)
		this->apply();

	glUniform3f(loc, vec3.x, vec3.y, vec3.z);

}

void ShaderProgram::setVector4(GLint loc, const Vector3& vec4, bool isApplied /*= false*/)
{
	if (!isApplied)
		this->apply();

	glUniform3f(loc, vec4.x, vec4.y, vec4.z);

}

void ShaderProgram::setMatrix3(GLint loc, const Matrix3x3& mat3, bool isApplied /*= false*/)
{
	if (!isApplied)
		this->apply();

	glUniformMatrix3fv(loc, 1, GL_FALSE, value_ptr(mat3));
}

void ShaderProgram::setMatrix4(GLint loc, const Matrix4x4& mat4, bool isApplied /*= false*/)
{
	if (!isApplied)
		this->apply();

	glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(mat4));

}

void ShaderProgram::setInterger(GLint loc, const int& value, bool isApplied /*= false*/)
{
	if (!isApplied)
		this->apply();

	if (loc== INVALID_UNIFORM_LOCATION)
	{
		Log("Invaild uniform location in shader.\n");
		return;
	}
	glUniform1i(loc, value);
}

void ShaderProgram::setFloat(GLint loc, const float& value, bool isApplied /*= false*/)
{
	if (!isApplied)
		this->apply();

	if (loc == INVALID_UNIFORM_LOCATION)
	{
		Log("Invaild uniform location in shader.\n");
		return;
	}
	glUniform1f(loc, value);
}

//
void ShaderProgram::setVector3(const char* locName, const Vector3& vec3, bool isApplied)
{
	if (!isApplied)
		this->apply();

	GLint loc = glGetUniformLocation(this->_programHandler, locName);
	if (loc == INVALID_UNIFORM_LOCATION)
	{
		Log("Invaild uniform location in shader.\n");
		return;
	}

	glUniform3f(loc, vec3.x, vec3.y, vec3.z);
}

void ShaderProgram::setVector3(GLint loc, const float& valueX, const float& valueY, const float& valueZ, bool isApplied /*= false*/)
{
	if (!isApplied)
		this->apply();

	if (loc == INVALID_UNIFORM_LOCATION)
	{
		Log("Invaild uniform location in shader.\n");
		return;
	}

	glUniform3f(loc,valueX, valueY, valueZ);
}

//
void ShaderProgram::setVector4(const char* locName, const Vector3& vec4, bool isApplied)
{
	if (!isApplied)
		this->apply();
	glUniform3f(glGetUniformLocation(this->_programHandler, locName), vec4.x, vec4.y, vec4.z);
}

//
void ShaderProgram::setMatrix3(const char* locName, const Matrix3x3& mat3, bool isApplied)
{
	if (!isApplied)
		this->apply();
	glUniformMatrix3fv(glGetUniformLocation(this->_programHandler, locName), 1, GL_FALSE, value_ptr(mat3));
}

//
void ShaderProgram::setMatrix4(const char* locName, const Matrix4x4& mat4, bool isApplied)
{
	if (!isApplied)
		this->apply();
	glUniformMatrix4fv(glGetUniformLocation(this->_programHandler, locName), 1, GL_FALSE, value_ptr(mat4));
}

void ShaderProgram::setInterger(const char* locName, const int& value, bool isApplied /*= false*/)
{
	if (!isApplied)
		this->apply();
	GLint location = glGetUniformLocation(this->_programHandler, locName);
	
	if (location == INVALID_UNIFORM_LOCATION)
	{
		Log("Invaild uniform location in shader.\n");
		return;
	}
	glUniform1i(location, value);
}

void ShaderProgram::setFloat(const char* locName, const float& value, bool isApplied /*= false*/)
{
	if (!isApplied)
		this->apply();
	glUniform1f(glGetUniformLocation(this->_programHandler, locName), value);
}


void ShaderProgram::destroy()
{
	if (_vertexShader){
		_vertexShader->destroy();
	}

	if (_geometryShader){
		_geometryShader->destroy();
	}

	if (_fragmentShader){
		_fragmentShader->destroy();
	}
}

GLint ShaderProgram::getLocation(const char* loc, bool isApplied /* = false */)
{
	if (!isApplied)
		this->apply();

	return glGetUniformLocation(this->_programHandler, loc);
}

