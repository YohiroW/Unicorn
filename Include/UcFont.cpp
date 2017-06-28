#include "UcFont.h"
#include <gl/glew.h>
NS_UNICORN;

//------static variables defination-------
bool Font::isInited = false;
std::string Font::DEFAULT_FONT = "res/fonts/TimesNewRoman.ttf";
FT_Library Font::FT_LIB = NULL;

//------Font Member Functions------
//ctor
Font::Font(std::string fontPath /* = DEFAULT_FONT */):
_fontSize(18)
{
	this->_initialize(fontPath);
}

//dtor
Font::~Font()
{

}

//
bool Font::_initialize(std::string fontPath)
{


	FT_Error err;
	if (!isInited)
	{
		//Initialize FreeType Library 
		err = FT_Init_FreeType(&FT_LIB);
		if (err != FT_Err_Ok)
		{
			//log error
			Log("ERROR: Free Type Initialize Failed..\n");
			return false;
		}
		isInited = true;
	}

	err = FT_New_Face(FT_LIB, fontPath.c_str(), 0, &_fontFace);
	if (err)
	{
		//log error
		return false;
	}

	FT_Set_Pixel_Sizes(_fontFace, 0, _fontSize);

	//setup the font loaded
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);		//disable the alignment
	
	//according to the default situation, just load 128 characters in ASCII
	for (GLubyte ch = 0; ch < 128; ++ch)
	{
		if (FT_Load_Char(_fontFace, ch, FT_LOAD_RENDER))
		{
			Log("ERROR: failed to load font glyph \n");
			continue;
		}

		//generate texture for the character 
		TextureID texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 
					 0,
					 GL_RED, 
					 _fontFace->glyph->bitmap.width,
					 _fontFace->glyph->bitmap.rows, 
					 0,
					 GL_RED,
					 GL_UNSIGNED_BYTE, 
					 _fontFace->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);

		SimpleChar character = 
		{
			texture,
			Vector2(_fontFace->glyph->bitmap.width, _fontFace->glyph->bitmap.rows),
			Vector2(_fontFace->glyph->bitmap_left, _fontFace->glyph->bitmap_top),
			_fontFace->glyph->advance.x
		};

		_characterMap.insert(std::pair<char, SimpleChar>(ch, character));
	}//

	FT_Done_Face(_fontFace);
	return true;
}

Font::SimpleChar Font::getCharFromMap(const char& key)
{
	return this->_characterMap[key];
}
