#include <cstdlib>
#include "UcObject.h"
using namespace Unicorn;

Object::ObjectMap Object::_objSets;

Object::Object():
_name("none"),
_isEnable(true)
{
}

Object::Object(const Object& obj)
{
	this->setEnabled(true);
}

Object::~Object()
{

}

Object* Object::findObjectByName(const std::string& name)
{
	return _objSets[name];
}

void Object::setEnabled(bool enable)
{
	if (enable)
	{
		_isEnable = true;
		this->onEnable();
		return;
	}
	//else 
	_isEnable = false;		//can not be seen(rendered) and so on...
	this->onDisable();
}

bool Object::isEnabled() const
{
	return _isEnable;
}

int Object::getHashCode() const
{
	return 0;
}

int Object::_hash(const char* str)
{
	//ELFhash
	unsigned int hash = 0;
	unsigned int x = 0;

	while (*str)
	{
		hash = (hash << 4) + (*str++); 
		if ((x = hash & 0xF0000000L) != 0)
		{
			hash ^= (x >> 24);
			hash &= ~x;
		}
	}
	return hash & 0x7FFFFFFF;
}

bool Object::equal(const Object* obj) const
{
	return obj->getHashCode() == this->_hashCode;
}

void Object::destroy()
{
	this->onDestroy();
}

void Object::onEnable()
{

}

void Object::onDisable()
{

}

void Object::onDestroy()
{

}

