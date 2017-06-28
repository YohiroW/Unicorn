#ifndef _UC_SHADER_H_
#define _UC_SHADER_H_
//
#include <gl/glew.h>
#include "UcObject.h"

namespace Unicorn
{
	class Shader : public Object
	{
	public:
		//
		static const unsigned int MAX_BUFFER_SIZE = 512;

		enum SamplerCoordinate
		{
			SC_NONE,
			SC_CLAMP,
			SC_REPEAT,
			SC_MIRRORED_REPEAT,
			SC_CLAMP_BORDER,
			SC_CLAMP_EDGE,
			SC_QUANTITY
		};

		enum SamplerType
		{
			ST_NONE,
			ST_1D,
			ST_2D,
			ST_3D,
			ST_CUBE,
			ST_QUANTITY
		};

		enum SamplerFilter
		{
			SF_NONE,
			SF_NEAREST,
			SF_LINEAR,
			SF_NEAREST_NEAREST,
			SF_NEAREST_LINEAR,
			SF_LINEAR_NEAREST,
			SF_LINEAR_LINEAR
		};

		enum ShaderType
		{
			VERTEX = GL_VERTEX_SHADER,
			FRAGMENT = GL_FRAGMENT_SHADER,
			GEOMETRY = GL_GEOMETRY_SHADER,
			COMPUTE = GL_COMPUTE_SHADER
			//TESSELLATION = -1;
		};

	public:
		//
		Shader();
		//Shader(const std::string& filePath, int inputNum, int outputNum, int constantNum, int samplerNum, bool profileOwner);
		virtual ~Shader();
		//
		bool initialize(const char* shaderPath, ShaderType shaderType);
		bool initializeWithCode(const char* shaderCode, ShaderType shaderType);
		//
		ShaderID getShaderHandler() const;
		//
		virtual void destroy();

	protected:
		//get source code from file
		char* _readShaderFromFile(const char* filePath) const;
		//shader type including 4 kinds, ref to enumeration
		ShaderID _compileShader(const char* filePath, ShaderType shaderType) const;
		//
		ShaderID _compileShaderCode(const char* code, ShaderType shaderType) const;
		
	private:
		//int _inputsNum;
		//std::string _inputsName;
		//VariableType* _inputsType;
		//VariableSematic* _inputsSematic;
		//
		//int _outputsNum;
		//std::string _outputsName;
		//VariableType* _outputsType;
		//VariableSematic* _outputsSematic;
		//
		//int _constantNum;  
		//std::string _constantName;
		//int _regeiterUsed;

		ShaderID _shaderHandler;
	};
}

#endif