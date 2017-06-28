#include "UcColor.h"
#include "UcMacros.h"
NS_UNICORN;


//
//color float rgba
//
const ColorFRGBA ColorFRGBA::WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const ColorFRGBA ColorFRGBA::BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const ColorFRGBA ColorFRGBA::RED(1.0f, 0.0f, 0.0f, 1.0f);
const ColorFRGBA ColorFRGBA::GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const ColorFRGBA ColorFRGBA::BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const ColorFRGBA ColorFRGBA::YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
const ColorFRGBA ColorFRGBA::ORANGE(1.0f, 0.5f, 0.3f , 1.0f);
const ColorFRGBA ColorFRGBA::CYAN(0.0f, 1.0f, 1.0f, 1.0f);
const ColorFRGBA ColorFRGBA::GRAY(0.77f, 0.77f, 0.77f, 1.0f);
const ColorFRGBA ColorFRGBA::DEFAULT(0.4f,0.4f,0.4f,1.0f);


ColorFRGBA::ColorFRGBA( float r /* = 0.1f */, 
						float g /* = 0.1f */, 
						float b /* = 0.1f */, 
						float a /* = 1.0f */)
						:R(r), G(g), B(b), A(a)
{
}

ColorFRGBA::ColorFRGBA(const ColorFRGBA& color)
: R(color.R), G(color.G), B(color.B)
{
}

//
//color byte rgba
//
const ColorBRGBA ColorBRGBA::WHITE(255,255,255,255);
const ColorBRGBA ColorBRGBA::BLACK(0,0,0,255);
const ColorBRGBA ColorBRGBA::RED(255,0,0,255);
const ColorBRGBA ColorBRGBA::GREEN(0,255,0,255);
const ColorBRGBA ColorBRGBA::BLUE(0,0,255,255);
const ColorBRGBA ColorBRGBA::ORANGE(255,150,0,255);
const ColorBRGBA ColorBRGBA::YELLOW(255,255,0,255);
const ColorBRGBA ColorBRGBA::CYAN(0,255,255,255);
const ColorBRGBA ColorBRGBA::GRAY(160,160,160,255);

ColorBRGBA::ColorBRGBA( GLubyte r /* = 255 */,
						GLubyte g /* = 255 */,
						GLubyte b /* = 255 */,
						GLubyte a /* = 255 */)
						:R(r), G(g), B(b), A(a)
{
}

ColorBRGBA::ColorBRGBA(const ColorBRGBA& color)
: R(color.R), G(color.G), B(color.B), A(color.A)
{
}