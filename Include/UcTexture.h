#ifndef _UC_TEXTURE_H_
#define _UC_TEXTURE_H_
//
#include <gl/glew.h>
#include <soil/SOIL.h>
#include "UcObject.h"

namespace Unicorn 
{
	typedef GLenum TextureUnit;

	class Texture :public Object
	{
	public:
		enum TextureType
		{
			TEXTURE1D,
			TEXTURE2D,
			TEXTURE3D,
			DIFFUSE,
			SPECULAR
		};

	public:
		Texture();
		~Texture();
		//
		bool initialize(const std::string& FileName, TextureUnit target = GL_TEXTURE_2D);
		//only when the method below was invoked, we can get textureId, width and height.
		bool load();
		bool loadDDS();
		void bind();
		void unbind();
		//	   
		int getTextureWidth() const;
		int getTextureHeight() const;
		TextureID getTextureHandler() const;
		void setTextureUnit(const unsigned int& unit);
		
		//
		virtual void destroy();
	
	protected:
		//
		TextureID _loadTexture(const char* path,
				     		   int imageFormat = GL_RGBA,
						       int internalFormat = GL_RGBA,
							   int level = 0,				//mipmap's level
							   int border = 0);

		TextureID _loadTextureDDS(const char* fileName);


	private:
		TextureID _texId;
		TextureUnit _textureTarget;
		std::string _fileName;
		int _width;
		int _height;

		//
		unsigned int _textureUnit;
	};
}

#endif