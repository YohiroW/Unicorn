#include "UcTweener.h"
NS_UNICORN;

//define static variables and methods
float Tweener::DEFAULT_DURATION = 1.2f;
MotionFormFunc Tweener::DEFAULT_MOTION_FUNC = MotionForm::linear;

Tweener::Tweener(Entity* entity) :
_entity(entity),
_transform()
{
	//add motion controller to entity
}

Tweener::~Tweener()
{

}

bool Tweener::initialize(Entity* entity)
{
	if (!entity)
	{
		//
		return false;
	}

	_entity = entity;
	_transform = _entity->getTransform();

	return true;
}

void Tweener::onUpdate()
{
	//be overrided
}

void Tweener::onEnable()
{
	//add onUpdate & onFinished to the virtual func of MotionCtrler
}

void Tweener::onDisable()
{
	//remove onUpdate & onFinished to the virtual func of MotionCtrler
}

void Tweener::onFinished()
{
	if (_destroyOnFinish)
		this->destroy();
}

void Tweener::destroy()
{

}
