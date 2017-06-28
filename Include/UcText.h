#ifndef _UC_TEXT_H_
#define _UC_TEXT_H_
//
#include "UcWidget.h"
#include "UcFont.h"
#include "UcColor.h"

namespace Unicorn
{
	class Text: public RenderableObject
	{
	public:
		Text(const std::string& content, const Vector2& pos = Vector2(0, 0));
		~Text();

		bool initialize(const std::string& content, const Vector2& pos = Vector2(0,0));

		virtual void onPreRender(Camera* cam);
		virtual void draw(float dt);
		virtual void onPostRender();

		GEN_FUNC(Font, _font, Font);
		GEN_FUNC(Vector2, _position, Position);
		GEN_FUNC(std::string, _textContent, Text);
		GEN_FUNC(float, _scaleFactor, Scale);
		GEN_FUNC(ColorFRGBA, _textColor, TextColor);

	protected:
		void _setup();
		void _renderText(const std::string& text, float x, float y, float scale, ColorFRGBA textColor);

	protected:
		std::string _textContent;
		Font _font;
		ColorFRGBA _textColor;
		float _scaleFactor;
		Vector2 _position;

		//TODO:
		GLuint _vao, _vbo;
		GLint _shaderLoc[3];
	};
}

#endif