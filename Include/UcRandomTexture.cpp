#include "UcRandomTexture.h"
#include "UcLogger.h"
NS_UNICORN;

RandomTexture::RandomTexture() :
_texHandler(INVALID_OGL_VALUE)
{
}

RandomTexture::~RandomTexture()
{
}

bool RandomTexture::initialize(const int& size)
{
	Vector3* rndTexBuffer = new Vector3[size];//
	//
	for (int i = 0; i < size; ++i)
	{
		rndTexBuffer[i].x = this->_getRandomFloat();
		rndTexBuffer[i].y = this->_getRandomFloat();
		rndTexBuffer[i].z = this->_getRandomFloat();
	}

	//setup
	glGenTextures(1, &_texHandler);
	
	glBindTexture(GL_TEXTURE_1D,_texHandler);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, size, 0.0f, GL_RGB, GL_FLOAT, rndTexBuffer);

	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	delete rndTexBuffer;//

	return GLCheckError();
}

void RandomTexture::bind(const TextureUnit& unit)
{
	glActiveTexture(unit);
	glBindTexture(GL_TEXTURE_1D, _texHandler);
}

TextureID RandomTexture::getTextureHandler() const
{
	if (_texHandler == INVALID_OGL_VALUE)
	{
		Log("Texture handler is invalid.\n");
		return 0;
	}
	return _texHandler;
}

void RandomTexture::destroy()
{
	if (_texHandler != INVALID_OGL_VALUE)
	{
		glDeleteTextures(1, &_texHandler);
	}
}

//------private------

float RandomTexture::_getRandomFloat() const
{
	return  2.0f * (float)rand() / RAND_MAX - 1.0f;	
}

