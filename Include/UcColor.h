#ifndef _UC_COLOR_H_
#define _UC_COLOR_H_
//
#include <gl/glew.h>
#include "UcVector3.h"

namespace Unicorn
{
	typedef Vector3 Color;

	struct ColorFRGBA
	{
		ColorFRGBA(float r = 0.1f, float g = 0.1f, float b = 0.1f, float a = 1.0f);
		ColorFRGBA(const ColorFRGBA& color);
		//the value shoule be limited within 0.0f ~ 1.0f
		float R, G, B, A;

		static const ColorFRGBA WHITE;
		static const ColorFRGBA BLACK;
		static const ColorFRGBA RED;
		static const ColorFRGBA GREEN;
		static const ColorFRGBA BLUE;
		static const ColorFRGBA YELLOW;
		static const ColorFRGBA ORANGE;
		static const ColorFRGBA CYAN;
		static const ColorFRGBA GRAY;
		static const ColorFRGBA DEFAULT;

	};

	struct ColorBRGBA
	{
		ColorBRGBA(GLubyte r = 255, GLubyte g = 255, GLubyte b = 255, GLubyte a = 255);
		ColorBRGBA(const ColorBRGBA& color);

		//RGBA range from 0 ~ 255
		GLubyte R, G, B, A;

		static const ColorBRGBA WHITE;
		static const ColorBRGBA BLACK;
		static const ColorBRGBA RED;
		static const ColorBRGBA GREEN;
		static const ColorBRGBA BLUE;
		static const ColorBRGBA ORANGE;
		static const ColorBRGBA YELLOW;
		static const ColorBRGBA CYAN;
		static const ColorBRGBA GRAY;
	};
}

#endif