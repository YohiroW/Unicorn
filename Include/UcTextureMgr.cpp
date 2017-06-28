#include "UcTextureMgr.h"

//#include "freeImage/FreeImage.h"
using namespace Unicorn;

TextureMgr* TextureMgr::_instance = NULL;

unsigned int TextureMgr::CUR_TEXTURE_UNIT = 0;

TextureMgr::TextureMgr()
{
}

TextureMgr::~TextureMgr()
{
	UCSafeDelete(_instance);
}

bool TextureMgr::initialize()
{
	MEM_SET_ZERO(_textureUnit);

	return true;
}

TextureID TextureMgr::loadTexture(const char* path, int imageFormat /* = GL_RGB */, int internalFormat /* = GL_RGB */, int level /* = 0 */, int border /* = 0 */)
{
	GLuint texId;
	//-1- generate a texture in opengl
	glGenTextures(1, &texId); //@p1 size @p2 texture id	

	//-2- use external lib to load image to cache
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
	
	//-3- bind current texture to set parameters
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexImage2D(GL_TEXTURE_2D, level, internalFormat, width, height, border, imageFormat, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	//-4- specific parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//-5- unbind and free the cache image occupied
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	return texId;
}

TextureID TextureMgr::loadTexture(const char* path, bool alpha)
{
	GLuint texId;
	//-1- generate a texture in opengl
	glGenTextures(1, &texId); //-1 size -2 texture id	
	int width, height;
	//-2- use external lib to load image to cache
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, alpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	//-3- bind current texture to set parameters
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexImage2D(GL_TEXTURE_2D, 0, alpha ? GL_RGBA : GL_RGB, width, height, 0, alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	//-4- specific parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, alpha ? GL_CLAMP_TO_EDGE : GL_POLYGON_OFFSET_UNITS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, alpha ? GL_CLAMP_TO_EDGE : GL_POLYGON_OFFSET_UNITS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//-5- unbind and free the cache image occupied
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	return texId;

}

TextureMgr* TextureMgr::getInstance()
{
	if (!_instance)
	{
		_instance = new TextureMgr;
		if (!_instance)
		{
			UCSafeDelete(_instance);
		}
	}
	return _instance;
}

unsigned int TextureMgr::getNextTextureTarget()
{
	unsigned int unit = CUR_TEXTURE_UNIT;
	CUR_TEXTURE_UNIT++;
	return GL_TEXTURE0 + unit; 
}

Texture* TextureMgr::createTexture(const std::string& tex)
{
	Texture* texture = new Texture;
	if (texture && texture->initialize(tex))
	{
		//unsigned int unit = CUR_TEXTURE_UNIT;
		//texture->setTextureUnit(GL_TEXTURE0 + unit);
		//CUR_TEXTURE_UNIT++;
		_textures.push_back(texture);
		return texture;
	}
	else
	{
		UCSafeDelete(texture);
		return NULL;
	}
}

void TextureMgr::destroy()
{
	for (auto iter: _textures)
	{
		if (iter)
		{
			iter->destroy();
			UCSafeDelete(iter);
		}
		_textures.remove(iter);
	}
	
	_textures.clear();

	UCSafeDelete(_instance);
}

Texture* TextureMgr::createTextureDDS(const std::string& dds)
{
	Texture* texture = new Texture;
	if (texture && texture->initialize(dds))
	{
		_textures.push_back(texture);
		return texture;
	}
	else
	{
		UCSafeDelete(texture);
		return NULL;
	}
}



















//TextureID TextureMgr::loadTexture(const char* path, uint texID, uint imageFormat /* = GL_RGB */, uint internalFormat /* = GL_RGB */, uint level /* = 0 */, uint border /* = 0 */)
//{
//	//image format
//	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
//	//pointer to the image, once loaded
//	FIBITMAP *dib(0);
//	//pointer to the image data
//	BYTE* bits(0);
//	//image width and height
//	unsigned int width(0), height(0);
//	//OpenGL's image ID to map to
//	GLuint gl_texID;
//
//	//check the file signature and deduce its format
//	fif = FreeImage_GetFileType(path, 0);
//	//if still unknown, try to guess the file format from the file extension
//	if (fif == FIF_UNKNOWN)
//		fif = FreeImage_GetFIFFromFilename(path);
//	//if still unkown, return failure
//	if (fif == FIF_UNKNOWN)
//		return false;
//
//	//check that the plugin has reading capabilities and load the file
//	if (FreeImage_FIFSupportsReading(fif))
//		dib = FreeImage_Load(fif, path);
//	//if the image failed to load, return failure
//	if (!dib)
//		return -1;
//
//	//retrieve the image data
//	bits = FreeImage_GetBits(dib);
//	//get the image width and height
//	width = FreeImage_GetWidth(dib);
//	height = FreeImage_GetHeight(dib);
//	//if this somehow one of these failed (they shouldn't), return failure
//	if ((bits == 0) || (width == 0) || (height == 0))
//		return false;
//
//	//if this texture ID is in use, unload the current texture
//	if (_textures.find(texID) != _textures.end())
//		glDeleteTextures(1, &(_textures[texID]));
//
//	//generate an OpenGL texture ID for this texture
//	glGenTextures(1, &gl_texID);
//	//store the texture ID mapping
//	_textures[texID] = gl_texID;
//	//bind to the new texture ID
//	glBindTexture(GL_TEXTURE_2D, gl_texID);
//	//store the texture data for OpenGL use
//	glTexImage2D(GL_TEXTURE_2D, level, internalFormat, width, height,
//		border, imageFormat, GL_UNSIGNED_BYTE, bits);
//
//	//Free FreeImage's copy of the data
//	FreeImage_Unload(dib);
//
//	//return success
//	return texID;
//}



