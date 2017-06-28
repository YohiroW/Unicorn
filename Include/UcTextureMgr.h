#ifndef TEXMGR_H
#define  TEXMGR_H
//
#include <gl/glew.h>
#include <soil/SOIL.h>
#include <list>
#include "UcConfig.h"
#include "UcObject.h"
#include "UcTexture.h"

namespace Unicorn
{
	class TextureMgr: public Object
	{
	public:
		//----------static----------
		//next texture unit you can active
		static unsigned int CUR_TEXTURE_UNIT;

		//when invoked, return texture unit 
		static unsigned int getNextTextureTarget();

	public:
		virtual ~TextureMgr();
		//mainly initialize texture unit 
		bool initialize();
		//TextureID <0 is where error happens 
		TextureID loadTexture(const char* path,
							  int imageFormat = GL_RGB,
							  int internalFormat = GL_RGB,
							  int level = 0,				//mipmap's level
							  int border = 0);				
		//+2 reload
		TextureID loadTexture(const char* path, bool alpha = false);
		//singleton
		static TextureMgr* getInstance();
		//create and add to list
		Texture* createTexture(const std::string& tex);
		Texture* createTextureDDS(const std::string& dds);
		//
		bool bindTexture(const int& texID);
		bool unbindTexture(const int& texID);
		void unbindAllTextures();
		//
		virtual void destroy();

	private:
		TextureMgr();
	
	private:
		//
		static TextureMgr* _instance;
		//id - texture
		std::list<Texture*> _textures;
		//
		int _textureUnit[MAX_TEXTURE_TARGET_COUNT];
	};

}

#endif