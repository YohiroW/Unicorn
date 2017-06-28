#ifndef _UC_QUATERNION_H_
#define _UC_QUATERNION_H_
//
#include <cmath>
#include <glm/gtc/quaternion.hpp>
#include "UcVector3.h"

namespace Unicorn
{
	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(Vector3 euler);
		Quaternion(float x, float y, float z, float w);
		~Quaternion();

		Quaternion slerp(Quaternion quat1, Quaternion quat2, float factor);
		Quaternion rotate(const Vector3& axis, const float& angle);
		


	private:
		//
		float _x, _y, _z, _w;

	};

}

#endif