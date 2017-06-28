#include "UcMainCamera.h"
NS_UNICORN;

MainCamera* MainCamera::_instance = NULL;

MainCamera::MainCamera():
Camera()
{
}

MainCamera::~MainCamera()
{

}

bool MainCamera::initialize()
{
	return true;
}

MainCamera* MainCamera::getInstance()
{
	if (!_instance)
	{
		_instance = new MainCamera();
		if (!_instance->initialize() && _instance)
		{
			UCSafeDelete(_instance);
			return NULL;
		}
	}
	return _instance;
}

