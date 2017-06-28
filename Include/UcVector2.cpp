#include "UcVector2.h"
#include <cmath>
using namespace Unicorn;



//
//realize
//
Vector2::Vector2(float _x, float _y)
: x(_x), y(_y)
{
}

Vector2::Vector2(const Vector2& _vec2)
{
	this->x = _vec2.x;
	this->y = _vec2.y;
}

Vector2::~Vector2()
{
}

Vector2 Vector2::operator+ (const Vector2& _vec2) const
{
	return Vector2(this->x + _vec2.x, this->y + _vec2.y);
}

Vector2 Vector2::operator- (const Vector2& _vec2) const
{
	return Vector2(this->x - _vec2.x, this->y - _vec2.y);
}

float Vector2::dot(const Vector2& _vec2) const
{
	return this->x* _vec2.x + this->y* _vec2.y;
}

float Vector2::magnilize() const
{
	return sqrt(this->x* this->x + this->y* this->y);
}

Vector2 Vector2::normalize() const
{
	Vector2 norm;
	float m = this->magnilize();
	norm.x = x / m;
	norm.y = y / m;
	return norm;
}

float Vector2::distance(const Vector2& _vec2) const
{
	return	sqrt(_vec2.x* _vec2.x + _vec2.y* _vec2.y);
}
