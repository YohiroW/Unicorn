/********************************************************************
created:	2017/01/26
filename: 	Vector3.h
file ext:	h
author:		Yohiro

purpose:
*********************************************************************/
#ifndef Vector3_H
#define Vector3_H
//
#include <cmath>
#include "UcMacros.h"
//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Unicorn
{
	class Vector3
	{
		//
	public:
		float x, y, z;
		//static const 
		//----------------------------
		static Vector3 ZERO;
		static Vector3 IDENTITY;
		static Vector3 AXIS_X;
		static Vector3 AXIS_Y;
		static Vector3 AXIS_Z;

		//static method
		//----------------------------
		static Vector3 dot(const Vector3& v1, const Vector3& v2);
		static Vector3 cross(const Vector3& v1, const Vector3& v2);

	public:
		//----------------------------
		Vector3() :x(0),y(0),z(0){}
		Vector3(float _x, float _y, float _z);
		Vector3(const Vector3& _vec3);
		Vector3(const glm::vec3& vec);

		//
		Vector3 operator +(const Vector3& _vec3) const;
		Vector3 operator -(const Vector3& _vec3) const;
		Vector3 operator *(const float& value) const;
		Vector3 operator =(const glm::vec3& value) const;

		//
		float operator [](const int& index) const;
		float operator [](const char* dim) const;
		//
		float dot(const Vector3& _vec3) const;
		float magnilize() const;
		float magnilizeSquare() const;
		float distance(const Vector3& _vec3) const;
		float distanceSquare(const Vector3& _vec3) const;
		Vector3 normalize() const;
		Vector3 cross(const Vector3& vec);

		~Vector3(){};

	};//End class Vector3 declare


}//
#endif // !Vector3_H



