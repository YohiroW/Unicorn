#ifndef _UC_CUBE_H_
#define _UC_CUBE_H_
//
#include <gl/glew.h>
#include "UcObject.h"
#include "UcTextureMgr.h"
#include "UcRenderableObject.h"
#include "UcShaderProgram.h"
#include "UcRenderData.h"

namespace Unicorn
{
	class Cube: public RenderableObject
	{
	public:
		Cube();
		~Cube(); 
		//
		bool initialize();
		//
		virtual void onPreRender(Camera* cam);
		virtual void onPostRender();
		virtual void draw(float dt);
		virtual void destroy();

		virtual void attachTexture(Texture* texture);
		virtual void attachTexture(const char* path);
		

	protected:
		void _setup();

	private:
		static GLuint _vao, _vbo;
		Texture* _texture;

		GLint _shaderLoc[5];
	
		//
		GLuint _textureUnit;
	
	};
}

#endif
