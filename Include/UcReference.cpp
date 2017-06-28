#include "UcReference.h"
using namespace Unicorn;

Reference::Reference():
_count(0),
_refObject(0)
{
}

Reference::Reference(Reference& ref)
{
	_refObject = ref._refObject;

	if (ref._refObject)
	{
		ref._count++;
	}
	_count = ref._count;
}

Reference::~Reference()
{
	_count--;
	if (_count == 0 && _refObject)
		delete _refObject;
}


Reference& Reference::operator =(Reference& ref)
{
	if (this != &ref)
	{
		_count--;
		if (_refObject != ref._refObject)
		{
			delete _refObject;
		}

		_refObject = ref._refObject;
		if (ref._refObject)
		{
			ref._count++;
		}
		_count = ref._count;
	}

	return *this;
}

Reference* Reference::operator->()
{
	return this;
}

bool Reference::operator ==(Reference& ref)
{
	return _refObject == ref._refObject;
}

bool Reference::operator !=(Reference& ref)
{
	return _refObject != ref._refObject;
}

void Reference::dispose()
{
	delete this;
}

void Reference::incRef()
{
	++_count;
}

void Reference::decRef()
{
	--_count;
}

unsigned int Reference::getRefCount() const
{
	return _count;
}
