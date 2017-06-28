#include "UcShaderMgr.h"
#include "UcShaderProgram.h"
NS_UNICORN;

//define static variables
//--------------------------------------------------------------
ShaderMgr::ShaderProgramList ShaderMgr::_shaderProgramList = ShaderMgr::ShaderProgramList();

ShaderMgr* ShaderMgr::_instance = NULL;
ShaderProgram* ShaderMgr::DEFAULT = NULL;
ShaderProgram* ShaderMgr::DEFAULT_SKYBOX = NULL;
ShaderProgram* ShaderMgr::DEFAULT_PARTICLE = NULL;
ShaderProgram* ShaderMgr::DEFAULT_MODEL = NULL;
ShaderProgram* ShaderMgr::DEFAULT_BILLBOARD = NULL;
ShaderProgram* ShaderMgr::DEFAULT_FONT = NULL;



const char* ShaderMgr::DEFAULT_VERTEX_SHADER = "res/shader/default_vertexShader.vs";
const char* ShaderMgr::DEFAULT_FRAGMENT_SHADER = "res/shader/default_fragShader.frag";

const char* ShaderMgr::DEFAULT_SKYBOX_VS = "res/shader/default_skybox.vs";
const char* ShaderMgr::DEFAULT_SKYBOX_FS = "res/shader/default_skybox.frag";

const char* ShaderMgr::DEFAULT_PARTICLE_VS = "res/shader/default_particle.vs";
const char* ShaderMgr::DEFAULT_PARTICLE_FS = "res/shader/default_particle.frag";

const char* ShaderMgr::DEFAULT_MODEL_VS = "res/shader/default_model.vs";
const char* ShaderMgr::DEFAULT_MODEL_FS = "res/shader/default_model.frag";

const char* ShaderMgr::DEFAULT_BILLBOARD_VS = "res/shader/default_billboard.vs";
const char* ShaderMgr::DEFAULT_BILLBOARD_FS = "res/shader/default_billboard.frag";

const char* ShaderMgr::DEFAULT_FONT_VS = "res/shader/font.vs";
const char* ShaderMgr::DEFAULT_FONT_FS = "res/shader/font.frag";


//
//const char* ShaderMgr::DEFAULT_BILLBOARD_VS =
//"#version 420\n "
//
//"layout(location = 0) in vec3 position; \n "
//
//"void main()\n"
//"{ \n "
//"gl_Position = vec4(position, 1.0); \n "
//"} \n";
//
//
//const char* ShaderMgr::DEFAULT_BILLBOARD_FS =
//"#version 420\n "
//
//"in vec2 texCoords; \n"
//"out vec4 color;\n"
//
//"uniform sampler2D colorMap;\n "
//
//"void main()\n "
//"{\n"
//"color = texture(colorMap, texCoords);\n"
//"if (color.r == 0 && color.g == 0 && color.b == 0)\n"
//"discard;\n"
//" }\n";
//
//
//const char* ShaderMgr::DEFAULT_BILLBOARD_GS =
//"#version 420\n"
//
//"layout(points) in;\n"
//"layout(triangle_strip) out;\n"
//"layout(max_vertices = 4) out;\n"
//
//"uniform mat4 gVP; \n"
//"uniform vec3 gCameraPos; \n"
//
//"out vec2 TexCoord; \n"
//
//"void main()\n"
//"{\n"
//"vec3 Pos = gl_in[0].gl_Position.xyz;\n"
//"vec3 toCamera = normalize(gCameraPos - Pos);\n"
//"vec3 up = vec3(0.0, 1.0, 0.0);\n"
//"vec3 right = cross(toCamera, up);\n"
//
//"Pos -= (right * 0.5);\n"
//"gl_Position = gVP * vec4(Pos, 1.0);\n"
//"TexCoord = vec2(0.0, 0.0);\n"
//"EmitVertex();\n"
//
//"Pos.y += 1.0;\n"
//"gl_Position = gVP * vec4(Pos, 1.0);\n"
//"TexCoord = vec2(0.0, 1.0);\n"
//"EmitVertex();\n"
//
//"Pos.y -= 1.0;\n"
//"Pos += right;\n"
//"gl_Position = gVP * vec4(Pos, 1.0);\n"
//"TexCoord = vec2(1.0, 0.0);\n"
//"EmitVertex();\n"
//
//"Pos.y += 1.0;\n"
//"gl_Position = gVP * vec4(Pos, 1.0);\n"
//"TexCoord = vec2(1.0, 1.0);\n"
//"EmitVertex();\n"
//
//"EndPrimitive();\n"
//"}\n";



ShaderMgr::ShaderMgr()
{
}

ShaderMgr::~ShaderMgr()
{
	this->destroy();
}

ShaderMgr* ShaderMgr::getInstance()
{
	if (!_instance)
	{
		_instance = new ShaderMgr;
		if (!_instance)
		{
			UCSafeDelete(_instance);
			return NULL;
		}
	}
	return _instance;
}

bool ShaderMgr::initialize()
{
	//TODO
	DEFAULT = this->createShaderProgram(DEFAULT_VERTEX_SHADER,
										DEFAULT_FRAGMENT_SHADER);
	
	DEFAULT_SKYBOX = this->createShaderProgram(DEFAULT_SKYBOX_VS, 
		                                       DEFAULT_SKYBOX_FS);

	DEFAULT_MODEL = this->createShaderProgram(DEFAULT_MODEL_VS, DEFAULT_MODEL_FS);



	return true;
}

Shader* ShaderMgr::createShader(const char* shaderFile, Shader::ShaderType shaderType) const
{
	Shader* shader = new Shader;
	if (shader && shader->initialize(shaderFile, shaderType))
	{
		//add to memory pool
		return shader;
	}
	else
	{
		UCSafeDelete(shader);
		return NULL;
	}
}

Shader* ShaderMgr::createShaderWithCode(const char* shaderCode, Shader::ShaderType shaderType) const
{
	Shader* shader = new Shader;
	if (shader && shader->initializeWithCode(shaderCode, shaderType))
	{
		//add to memory pool
		return shader;
	}
	else
	{
		UCSafeDelete(shader);
		return NULL;
	}
}

ShaderProgram* ShaderMgr::createShaderProgram(Shader* vertexShader, Shader* fragShader) const
{
	ShaderProgram* shaderProgram = new ShaderProgram;
	if (shaderProgram && shaderProgram->initialize(vertexShader, fragShader))
	{
		//add to memory pool
		_shaderProgramList.push_back(shaderProgram);
		return shaderProgram;
	}
	else
	{
		UCSafeDelete(shaderProgram);
		return NULL;
	}
}

ShaderProgram* ShaderMgr::createShaderProgram(const char* vertexShader, const char* fragShader) const
{
	ShaderProgram* shaderProgram = new ShaderProgram;
	Shader* vs = this->createShader(vertexShader,Shader::ShaderType::VERTEX);
	Shader* fs = this->createShader(fragShader, Shader::ShaderType::FRAGMENT);
	if (shaderProgram && shaderProgram->initialize(vs,fs))
	{
		//add to memory pool
		_shaderProgramList.push_back(shaderProgram);
		return shaderProgram;
	}
	else
	{
		UCSafeDelete(shaderProgram);
		return NULL;
	}
}

ShaderProgram* ShaderMgr::createShaderProgram(Shader* vertexShader, Shader* fragShader, Shader* geometryShader) const
{
	ShaderProgram* shaderProgram = new ShaderProgram;
	if (shaderProgram && shaderProgram->initialize(vertexShader, fragShader, geometryShader))
	{
		//add to memory pool
		_shaderProgramList.push_back(shaderProgram);
		return shaderProgram;
	}
	else
	{
		UCSafeDelete(shaderProgram);
		return NULL;
	}
}

ShaderProgram* ShaderMgr::createShaderProgram(const char* vertexShader, const char* fragShader, const char* geometryShader) const
{
	ShaderProgram* shaderProgram = new ShaderProgram;

	Shader* vs = this->createShader(vertexShader, Shader::ShaderType::VERTEX);
	Shader* fs = this->createShader(fragShader, Shader::ShaderType::FRAGMENT);
	Shader* gs = this->createShader(geometryShader, Shader::ShaderType::GEOMETRY);

	if (shaderProgram && shaderProgram->initialize(vs, fs, gs))
	{
		//add to memory pool
		_shaderProgramList.push_back(shaderProgram);
		return shaderProgram;
	}
	else
	{
		UCSafeDelete(shaderProgram);
		return NULL;
	}
}

ShaderProgram* ShaderMgr::createShaderProgramWithCode(const char* vertexShaderCode, const char* fragShaderCode, const char* geometryShaderCode) const
{
	ShaderProgram* shaderProgram = new ShaderProgram;

	Shader* vs = this->createShaderWithCode(vertexShaderCode, Shader::ShaderType::VERTEX);
	Shader* fs = this->createShaderWithCode(fragShaderCode, Shader::ShaderType::FRAGMENT);
	Shader* gs = this->createShaderWithCode(geometryShaderCode, Shader::ShaderType::GEOMETRY);

	if (shaderProgram && shaderProgram->initialize(vs, fs, gs))
	{
		//add to memory pool
		_shaderProgramList.push_back(shaderProgram);
		return shaderProgram;
	}
	else
	{
		UCSafeDelete(shaderProgram);
		return NULL;
	}
}

void ShaderMgr::destroy()
{
	for (auto iter : _shaderProgramList)
	{
		iter->destroy();
	}
	UCSafeDelete(_instance);
}

void ShaderMgr::deleteShader(Shader* shader)
{
	UCSafeDelete(shader);
}

