#ifndef _UC_SHADERMGR_H_
#define  _UC_SHADERMGR_H_
//
#include <gl/glew.h>
#include <vector>
#include "UcShader.h"

namespace Unicorn
{
	class ShaderProgram;

	class ShaderMgr
	{
	public:
		//
		static ShaderProgram* DEFAULT;
		static ShaderProgram* DEFAULT_SKYBOX;
		static ShaderProgram* DEFAULT_PARTICLE;
		static ShaderProgram* DEFAULT_MODEL;
		static ShaderProgram* DEFAULT_BILLBOARD;
		static ShaderProgram* DEFAULT_FONT;

		//
		static const char* DEFAULT_VERTEX_SHADER;
		static const char* DEFAULT_FRAGMENT_SHADER;
		static const char* DEFAULT_SKYBOX_VS;
		static const char* DEFAULT_SKYBOX_FS;
		static const char* DEFAULT_PARTICLE_VS;
		static const char* DEFAULT_PARTICLE_FS;
		static const char* DEFAULT_MODEL_VS;
		static const char* DEFAULT_MODEL_FS;
		//
		static const char* DEFAULT_BILLBOARD_VS;
		static const char* DEFAULT_BILLBOARD_FS;
		static const char* DEFAULT_BILLBOARD_GS;

		static const char* DEFAULT_FONT_VS;
		static const char* DEFAULT_FONT_FS;

		//	
		typedef std::vector<ShaderProgram*> ShaderProgramList;

	public:
		//
		virtual ~ShaderMgr();
		//
		static ShaderMgr* getInstance();
		//
		bool initialize();
		//
		Shader* createShader(const char* shaderFile, Shader::ShaderType shaderType) const;
		Shader* createShaderWithCode(const char* shaderCode, Shader::ShaderType shaderType) const;
		//
		ShaderProgram* createShaderProgram(Shader* vertexShader, Shader* fragShader) const;
		ShaderProgram* createShaderProgram(Shader* vertexShader, Shader* fragShader, Shader* geometryShader) const;
		ShaderProgram* createShaderProgram(const char* vertexShader, const char* fragShader) const;
		ShaderProgram* createShaderProgram(const char* vertexShader, const char* fragShader, const char* geometryShader) const;
		ShaderProgram* createShaderProgramWithCode(const char* vertexShaderCode, const char* fragShaderCode, const char* geometryShaderCode) const;

		//
		void deleteShader(Shader* shader);
		//
		void destroy();

	protected:
		
	private:
		ShaderMgr();


	private:
		static ShaderMgr* _instance;

		static ShaderProgramList _shaderProgramList;
	};
}

#endif


