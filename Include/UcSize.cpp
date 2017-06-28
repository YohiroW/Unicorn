#include "UcSize.h"
#include <cmath>

using namespace Unicorn;
//
//realize
//
Size::Size(float _x, float _y)
: width(_x), height(_y)
{
}

Size::~Size()
{
}

Size Size::operator+ (const Size& _vec2) const
{
	return Size(this->width + _vec2.width, this->height + _vec2.height);
}

Size Size::operator- (const Size& _vec2) const
{
	return Size(this->width - _vec2.width, this->height - _vec2.height);
}
