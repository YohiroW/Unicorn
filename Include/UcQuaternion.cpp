#include "UcQuaternion.h"
NS_UNICORN;


Quaternion::Quaternion():
_x(0), _y(0), _z(0), _w(1)
{

}

Quaternion::Quaternion(Vector3 euler):
_x(0), _y(0), _z(0), _w(1)
{
	
}


Quaternion::Quaternion(float x, float y, float z, float w) :
_x(x), _y(y), _z(z), _w(w)
{
}


Quaternion::~Quaternion()
{

}

Quaternion Quaternion::rotate(const Vector3& axis, const float& angle)
{
	float value = sin(angle / 2);
	this->_x = axis.x * value;
	this->_y = axis.y * value;
	this->_z = axis.z * value;
	this->_w = cos(angle / 2);

	return *this;
}

Quaternion Quaternion::slerp(Quaternion quat1, Quaternion quat2, float factor)
{
	return Quaternion();
}