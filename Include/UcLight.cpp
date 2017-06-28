#include "UcLight.h"
NS_UNICORN;


Light::Light(const Vector3& lightSource,
	const LightType& lightType,
	const float& ambt /* = 0.5f */,
	const float& diff /* = 1.0f */,
	const float& spec /* = 32.0f */)
	:_ambient(ambt),
	_diffuse(diff),
	_spec(spec),
	_lightType(lightType)
{
}

Light::~Light()
{

}

bool Light::initialize(const Vector3& lightSource, 
	                   const LightType& lightType, 
					   const float& ambt /*= 0.5f*/, 
					   const float& diff /*= 1.0f*/, 
					   const float& spec /*= 32.0f*/)
{


	return true;
}

void Light::_initPointLight()
{

}

void Light::_initAreaLight()
{

}

void Light::_initDirectionLight()
{

}

void Light::destroy()
{

}