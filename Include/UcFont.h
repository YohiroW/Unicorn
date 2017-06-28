#ifndef _UC_FONT_H_
#define _UC_FONT_H_
//
//free type 
#include <ft2build.h>
#include FT_FREETYPE_H
//
#include <map>
#include "UcVector2.h"
#include "UcWidget.h"

namespace Unicorn
{
	//class FontMgr: public Object
	//{
	//public:

	//public:
	//	bool initialize();


	//private:
	//	FontMgr* _instance;
	//	FT_Library _ftLibrary;

	//};


	class Font
	{
	public:
		//------inner struct------
		typedef struct 
		{
			TextureID textureID;
			Vector2 size;
			Vector2 bearing;
			unsigned int advanced;
		}SimpleChar;

		//------static default font------
		static std::string DEFAULT_FONT;		 //Times New Roman	
		static FT_Library FT_LIB;
		static bool isInited;


	public:
		Font(std::string fontPath = DEFAULT_FONT);
		~Font();

		//setter & getter
		GEN_FUNC(float, _fontSize, FontSize);
		SimpleChar getCharFromMap(const char& key);


	private:
		bool _initialize(std::string fontPath);


	private:
		FT_Face _fontFace;
		unsigned int _fontSize;

		//font map
		std::map<char, SimpleChar> _characterMap;
	};


}


#endif