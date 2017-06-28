#ifndef SIZE_H
#define SIZE_H

namespace Unicorn
{
	class Size
	{
	public:
		Size();
		Size(float _width, float _height);

		~Size();

	public:
		float width;
		float height;
	};
}
#endif

