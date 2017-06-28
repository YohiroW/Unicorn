#include "UcVector3.h"
NS_UNICORN;

//static const defination
//-------------------------------------------
Vector3 Vector3::ZERO(0.0f,0.0f,0.0f);
Vector3 Vector3::IDENTITY(1.0f ,1.0f, 1.0f);
Vector3 Vector3::AXIS_X(1.0f, 0.0f, 0.0f);
Vector3 Vector3::AXIS_Y(0.0f, 1.0f, 0.0f);
Vector3 Vector3::AXIS_Z(0.0f, 0.0f, 1.0f);

//static methods
//--------------------------------------------

Vector3 Vector3::dot(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x* v2.x, v1.y* v2.y, v1.z* v2.z);
}

Vector3 Vector3::cross(const Vector3& v1, const Vector3& v2)
{
	glm::vec3 result = glm::cross(glm::vec3(v1.x, v1.y, v1.z), glm::vec3(v2.x, v2.y, v2.z));
	return Vector3(result.x, result.y, result.z);

	//return Vector3(v1.y * v2.z - v1.z * v2.y,
	//	           v1.z * v2.x - v1.x * v2.z,
	//			   v1.x * v2.y - v1.y * v2.x);
}

//member function
//-----------------------------------------------
Vector3::Vector3(float _x, float _y, float _z)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
}

Vector3::Vector3(const Vector3& _vec3)
{
	this->x = _vec3.x;
	this->y = _vec3.y;
	this->z = _vec3.z;
}

Vector3::Vector3(const glm::vec3& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}

float Vector3::dot(const Vector3& _vec3) const
{
	return this->x* _vec3.x + 
		   this->y* _vec3.y +
		   this->z* _vec3.z;
}

float Vector3::magnilize() const
{
	return this->distance(*this);
}

float Vector3::magnilizeSquare() const
{
	return this->x* this->x + 
		   this->y* this->y +
		   this->z* this->z;
}

float Vector3::distance(const Vector3& _vec3) const
{
	return sqrt(this->x * _vec3.x +
				this->y * _vec3.y +
				this->z * _vec3.z);
}

float Vector3::distanceSquare(const Vector3& _vec3) const
{
	return this->x * _vec3.x +
	       this->y * _vec3.y +
		   this->z * _vec3.z;
}

Vector3 Vector3::normalize() const
{
	//float len = this->magnilize();

	//return Vector3(this->x/len, this->y/len, this->z/len);
	//
	glm::vec3 result = glm::normalize(glm::vec3(this->x,this->y,this->z));
	return Vector3(result.x, result.y, result.z);
}

Vector3 Vector3::cross(const Vector3& vec)
{
	return Vector3(
		this->y * vec.z - vec.y * this->z,
		this->z * vec.x - vec.z * this->x,
		this->x * vec.y - vec.x * this->y);
}

Vector3 Vector3::operator*(const float& value) const
{
	return Vector3(x* value, y* value, z* value);
}

Vector3 Vector3::operator-(const Vector3& _vec3) const
{
	return Vector3(x- _vec3.x, y- _vec3.y, z- _vec3.z);
}

Vector3 Vector3::operator+(const Vector3& _vec3) const
{
	return Vector3(x+ _vec3.x, y+ _vec3.y, z+ _vec3.z);
}

Vector3 Vector3::operator=(const glm::vec3& value) const
{
	return Vector3(value.x, value.y, value.z);
}

