/********************************************************************
	created:	2017/01/26
	filename: 	Vector2.h
	file ext:	h
	author:		Yohiro
	
	purpose:	
*********************************************************************/
#ifndef VECTOR2_H
#define VECTOR2_H
#include "UcMacros.h"

namespace Unicorn
{
	class Vector2
	{
	//
	public:
		float x, y;
		

	public:
		//
		Vector2() :x(0), y(0){}
		Vector2(float _x, float _y);
		Vector2(const Vector2& _vec2);
		//
		Vector2 operator +(const Vector2& _vec2) const;
		Vector2 operator -(const Vector2& _vec2) const;
		//
		float operator [](const int& index) const;
		float operator [](const char* dim) const;
		//
		UCInline float dot(const Vector2& _vec2) const;
		UCInline float magnilize() const;
		UCInline float distance(const Vector2& _vec2) const;
		UCInline Vector2 normalize() const;

		~Vector2();
		
	};//End class Vector2 declare

	
}//
#endif // !VECTOR2_H



