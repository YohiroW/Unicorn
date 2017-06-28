#include "UcEntity.h"
#include "UcRenderableObject.h"
NS_UNICORN;

Entity::Entity():
_parent(NULL),
_renderable(NULL),
_transform()
{
}

Entity::~Entity()
{
	
}

bool Entity::initialize(const std::string& name)
{
	this->setName(name);
	this->_hash(name.c_str());
	
	return true;
}

void Entity::setParent(Entity* parent)
{
	_parent = parent;
	_transformToParent(parent);
}

Entity* Entity::getParent() const
{
	return _parent;
}

void Entity::destroy()
{
	_renderable->destroy();

	delete this;
}

void Entity::setPosition(const Vector3& pos)
{
	if (_renderable)
		_renderable->translate(pos);
}

Vector3 Entity::getPosition() const
{
	if (_renderable)
		return _renderable->getTransform().Position();
	return Vector3::ZERO;
}

void Entity::setScale(const Vector3& scale)
{
	//
	_renderable->scale(scale);
}

Vector3 Entity::getScale() const
{
	return _renderable->getTransform().Scale();
}

void Entity::setEuler(const Vector3& euler)
{
	_renderable->rotateWithEuler(euler);
}

Vector3 Entity::getEuler() const
{
	return _renderable->getTransform().Euler();
}

void Entity::_transformToParent(Entity* parent)
{
	_transform.transformTo(parent->getTransform());
}

Transform Entity::getTransform() const
{
	return _transform;
}

void Entity::attachRenderable(RenderableObject* renderable)
{
	if (_renderable)
	{
		//can not attach a renderable 
		return;
	}
	_renderable = renderable;
}

RenderableObject* Entity::getRenderable() const
{
	return _renderable;
}

void Entity::rotate(const float& degree, const Vector3& axis)
{
	_renderable->rotate(RADIANS(degree), axis);
}

void Entity::update(float dt)
{

}