#include "UcSmartPtr.h"

NS_UNICORN;

template<class T>
SmartPtr<T>::SmartPtr():
_refCount(NULL),
_refPtr(NULL)
{
}

template<class T>
SmartPtr<T>::SmartPtr(T* ptr) :
_refCount(new int(1)),
_refPtr(ptr)
{
}


template<class T>
SmartPtr<T>::~SmartPtr()
{
	if (_refCount)
	{
		(*_refCount)--;

		if (*_refCount <= 0 && _refPtr != NULL)
		{
			delete _refPtr;
			delete _refCount;
		}
	}
}

template<class T>
SmartPtr<T>::SmartPtr(const SmartPtr<T>& ptr)
{
	_refPtr = ptr._refPtr;

	if (ptr._refPtr != NULL)
	{
		(*ptr._refCount)++;
	}
	_refCount = ptr._refCount;
}

template<class T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T>& ptr)
{
	if (this != &ptr)
	{
		(*_refCount)--;

		if (*_refCount <= 0 && _refPtr != NULL)
		{
			delete _refPtr;
		}

		_refPtr = ptr._refPtr;

		if (ptr._refPtr != NULL)
		{
			(*ptr._refCount)++;
		}
		_refCount = ptr._refCount;
	}

	return *this;
}

template<class T>
bool SmartPtr<T>::operator!=(const SmartPtr<T>& ptr)
{
	return _refPtr != ptr._refPtr;
}

template<class T>
bool SmartPtr<T>::operator==(const SmartPtr<T>& ptr)
{
	return _refPtr == ptr._refPtr;
}

template<class T>
T* SmartPtr<T>::operator->()
{
	return _refPtr;
}

template<class T>
inline int SmartPtr<T>::getRefCount() const{
	return *_refCount;
}
