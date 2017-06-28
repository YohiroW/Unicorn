#include "UcTexture.h"
NS_UNICORN;

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

Texture::Texture():
_width(0),
_height(0),
_texId(INVALID_OGL_VALUE)
{
}

Texture::~Texture()
{
}

bool Texture::initialize(const std::string& fileName, TextureUnit target /*= GL_TEXTURE_2D*/)
{
	this->_fileName = fileName;
	this->_textureTarget = target;
	this->_name = fileName;

	return true;
}

bool Texture::load()
{
	//width¡¢height¡¢texId updated in the method below
	_texId = this->_loadTexture(_fileName.c_str());

	return (_texId != INVALID_OGL_VALUE) ;
}

bool Texture::loadDDS()
{
	_texId = this->_loadTextureDDS(_fileName.c_str());

	return (_texId != INVALID_OGL_VALUE);
}

void Texture::bind()
{
	//the unit actived have to be equal with texture id.
	GLuint unitActived = GL_TEXTURE0 + _texId;
	if (unitActived >=0 && unitActived < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)
	{
		glActiveTexture(unitActived);
		glBindTexture(_textureTarget, _texId);
	}
	else
	{
		Log("invaild texture unit was actived. \n");
	}

}

void Texture::unbind()
{
	glActiveTexture(GL_TEXTURE0 + _texId);
	glBindTexture(_textureTarget, 0);
}

int Texture::getTextureWidth() const
{
	return _width;
}

int Texture::getTextureHeight() const
{
	return _height;
}

TextureID Texture::getTextureHandler() const
{
	return _texId;
}

TextureID Texture::_loadTexture(const char* path, int imageFormat /*= GL_RGB*/, int internalFormat /*= GL_RGB*/, int level /*= 0*/, /*mipmap's level */ int border /*= 0*/)
{
	GLuint texId;
	//-1- generate a texture in opengl
	glGenTextures(1, &texId); //-1 size -2 texture id	
	int width, height;
	//-2- use external lib to load image to cache
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
	//-3- bind current texture to set parameters
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	//-4- specific parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//-5- unbind and free the cache image occupied
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	return texId;
}


void Texture::destroy()
{
	if (_texId != INVALID_OGL_VALUE)
	{
		glDeleteTextures(1, &_texId);
	}
}

TextureID Texture::_loadTextureDDS(const char* fileName)
{
	unsigned char header[124];

	FILE *fp;

	/* try to open the file */
	fp = fopen(fileName, "rb");
	if (fp == NULL){
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", fileName); getchar();
		return 0;
	}

	/* verify the type of file */
	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0) {
		fclose(fp);
		return 0;
	}

	/* get the surface desc */
	fread(&header, 124, 1, fp);

	unsigned int height = *(unsigned int*)&(header[8]);
	unsigned int width = *(unsigned int*)&(header[12]);
	unsigned int linearSize = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC = *(unsigned int*)&(header[80]);


	unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);
	/* close the file pointer */
	fclose(fp);

	unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch (fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(buffer);
		return 0;
	}

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	/* load the mipmaps */
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
			0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;

		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
		if (width < 1) width = 1;
		if (height < 1) height = 1;

	}

	free(buffer);

	return textureID;

}

void Texture::setTextureUnit(const unsigned int& unit)
{
	if ( unit >0 && unit < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)
	{
		_textureUnit = unit;
	}
}
