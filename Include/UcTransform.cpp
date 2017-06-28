#include "UcTransform.h"
NS_UNICORN;

Transform::Transform():
_position(Vector3::ZERO),
_scale(Vector3::IDENTITY),
_euler(Vector3::ZERO)
{
	_model = Matrix4x4();
} 

Transform::Transform(Matrix4x4 mat):
_position(Vector3::ZERO),
_scale(Vector3::IDENTITY),
_euler(Vector3::ZERO)
{
	_model = Matrix4x4();
}

Transform::~Transform()
{
}


Matrix4x4 Transform::translate(const Matrix4x4& mat4,const Vector3& vec)
{
	_model = glm::translate(mat4, glm::vec3(vec.x, vec.y, vec.z));

	_position.x = _model[3].x / _scale.x;
	_position.y = _model[3].y / _scale.y;
	_position.z = _model[3].z / _scale.z;

	return _model;
}

Matrix4x4 Transform::translate(const Vector3& vec)
{
	_model = glm::translate(_model, glm::vec3(vec.x, vec.y, vec.z));

	_position.x = _model[3].x / _scale.x;
	_position.y = _model[3].y / _scale.y;
	_position.z = _model[3].z / _scale.z;

	return _model;
}

Matrix4x4 Transform::rotate(const Matrix4x4& mat4,const float& degree, const Vector3& axis)
{
	//_euler.x = 2 * acos(_euler.x);
	//_euler.y = 2 * acos(_euler.y);
	//_euler.z = 2 * acos(_euler.z);

	_model = glm::rotate(mat4,degree ,glm::vec3(axis.x, axis.y, axis.z));
	return _model;
}

Matrix4x4 Transform::rotate(const float& degree, const Vector3& axis)
{
	_model = glm::rotate(_model, degree, glm::vec3(axis.x, axis.y, axis.z));
	return _model;
}

Matrix4x4 Transform::rotateWithEuler(const Vector3& euler)
{
	_euler = euler;
	
	//Y-Z-X
	glm::rotate(_model, euler.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::rotate(_model, euler.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::rotate(_model, euler.x, glm::vec3(1.0f, 0.0f, 0.0f));

	return _model;
}

Matrix4x4 Transform::scale(const Matrix4x4& mat4, const Vector3& scaleFactor)
{
	_scale = scaleFactor;
	_model = glm::scale(mat4, glm::vec3(scaleFactor.x, scaleFactor.y, scaleFactor.z));
	return _model;
}

Matrix4x4 Transform::scale(const Vector3& scaleFactor)
{
	_scale = scaleFactor;
	_model = glm::scale(_model, glm::vec3(scaleFactor.x, scaleFactor.y, scaleFactor.z));
	return _model;
}

void Transform::transformTo(Matrix4x4 mat)
{
	_model = mat * _model;
}

void Transform::transformTo(Transform parent)
{
	_model = parent.getModel()* _model;
}

Vector3 Transform::Position() const
{
	return _position;
}

Vector3 Transform::Scale() const
{
	return _scale;
}

Vector3 Transform::Euler() const
{
	return _euler;
}

void Transform::setModel(const Matrix4x4& mat)
{
	_model = mat;
}

Matrix4x4 Transform::getModel()
{
	return _model;
}

void Transform::setPosition(const Vector3& pos)
{
	this->translate(pos);
}
