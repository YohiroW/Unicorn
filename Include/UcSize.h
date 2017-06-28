#ifndef SIZE_H
#define SIZE_H
#include "UcMacros.h"
#include "UcReference.h"

namespace Unicorn
{
	class Size: public Reference
	{
		//
	public:
		float width, height;
		//
	public:
		//
		Size() :width(0), height(0){}
		Size(float _x, float _y);
		Size(const Size& _vec2);
		//
		Size operator +(const Size& _vec2) const;
		Size operator -(const Size& _vec2) const;
		//
		float operator [](const int& index) const;
		float operator [](const char* dim) const;

		~Size();

	};//End class Size declare


}//
#endif // !SIZE_H



