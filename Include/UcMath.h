#ifndef _UC_MATH_H_
#define _UC_MATH_H_
//
#include <cmath>
#include "UcMatrix.h"
#include "UcVector3.h"

namespace Unicorn
{
	class Math
	{
	public:
		static float getLength2(const Vector3& vec3);

		static const double PRECISION;

	public:
		static float clamp(const float& value, const float& floor, const float& limit)
		{
			if (value < floor)
				return floor;
			if (value > limit)
				return limit;
			return value;
		}

		static float clamp01(const float& value)
		{
			return clamp(value, 0, 1);
		}

		static bool approximate(const float& a,const float& b)
		{
			return (abs(a - b) < PRECISION);
		}


		static Matrix4x4 inverse(const Matrix4x4& mat)
		{
			return glm::inverse(mat);
		}

		static Vector3 getVector3FromMat4(const Matrix4x4& mat, const int& index)
		{
			return Vector3(mat[index].x, mat[index].y, mat[index].z);
		}

		static float getRandomIndex(const int& from, const int& to)
		{
			return rand() % (to - from + 1) + from;
		}

		static Vector3 getRandomVec3(const int& from, const int& to)
		{
			return Vector3(getRandomIndex(from, to),
				           getRandomIndex(from, to),
				           getRandomIndex(from, to));
		}



	};



}

#endif