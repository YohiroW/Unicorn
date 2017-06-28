#ifndef _UC_SHADER_PROGRAM_H_
#define _UC_SHADER_PROGRAM_H_
//
#include "UcShader.h"
#include "UcObject.h"
#include "UcMatrix.h"
#include "UcVector2.h"
#include "UcVector3.h"

namespace Unicorn
{	

	class ShaderProgram: public Object
	{
	public:
		ShaderProgram();

		virtual ~ShaderProgram();
		
		ShaderProgramID getShaderProgramID() const;
	
		bool initializeWithCode(const char* vertexShader, const char* fragShader, const char* geometryShader = NULL);	
		bool initialize(Shader* vertexShader, Shader* fragShader, Shader* geometryShader = NULL);

		void apply();
		//
		void setVector2(const char* locName, const Vector2& vec2, bool isApplied = false);
		void setVector2(GLint loc, const Vector2& vec2, bool isApplied = false);

		void setVector3(const char* locName, const Vector3& vec3, bool isApplied = false);
		void setVector3(GLint loc, const Vector3& vec3, bool isApplied = false);
		void setVector3(GLint loc, const float& valueX, const float& valueY, const float& valueZ, bool isApplied = false);

		void setVector4(const char* locName, const Vector3& vec4, bool isApplied = false);
		void setVector4(GLint loc, const Vector3& vec4, bool isApplied = false);

		void setMatrix3(const char* locName, const Matrix3x3& mat3, bool isApplied = false);
		void setMatrix3(GLint loc, const Matrix3x3& mat3, bool isApplied = false);

		void setMatrix4(const char* locName, const Matrix4x4& mat4, bool isApplied = false);
		void setMatrix4(GLint loc, const Matrix4x4& mat4, bool isApplied = false);

		void setInterger(const char* locName, const int& value, bool isApplied = false);		
		void setInterger(GLint loc, const int& value, bool isApplied = false);

		void setFloat(const char* locName, const float& value, bool isApplied = false);
		void setFloat(GLint loc, const float& value, bool isApplied = false);


		GLint getLocation(const char* loc, bool isApplied = false);

		virtual void destroy();

	protected:

		ShaderProgramID _linkShaderProgram(Shader* vertexShader, Shader* fragmentShader) const;
		ShaderProgramID _linkShaderProgram(Shader* vertexShader, Shader* fragmentShader, Shader* geometryShader) const;


	private:
		ShaderProgramID _programHandler;

		Shader* _vertexShader;
		Shader* _fragmentShader;
		Shader* _geometryShader;

	};
}



#endif