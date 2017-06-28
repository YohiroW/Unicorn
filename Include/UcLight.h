#ifndef _UC_LIGHT_H_
#define _UC_LIGHT_H_
//
#include "UcEntity.h"
#include "UcVector3.h"

namespace Unicorn
{
	enum LightType
	{
		POINT,
		DIRECTION,
		AREA
	};

	//Actually, this is a abstract light caster
	class Light : public Entity
	{
	public:
		//
		virtual ~Light();
		Light(const Vector3& lightSource, 
			  const LightType& lightType,
			  const float& ambt = 0.5f,
			  const float& diff = 1.0f,
			  const float& spec = 32.0f);

		//only area light can change the direction the light cast to
		bool initialize(const Vector3& lightSource,
						const LightType& lightType,
						const float& ambt = 0.5f,
						const float& diff = 1.0f,
						const float& spec = 32.0f);

		//to set direction the light cast to
		GEN_SGET_FUNC(Vector3, _lightDir, LightDirection);
		GEN_SGET_FUNC(Vector3,_lightSource,LightSource);
		GEN_SGET_FUNC(float, _ambient, Ambient);
		GEN_SGET_FUNC(float, _diffuse, Diffuse);
		GEN_SGET_FUNC(float, _spec,Specular);
		GEN_SGET_FUNC(float, _constant, Constant);
		GEN_SGET_FUNC(float, _linear, Linear);
		GEN_SGET_FUNC(float, _quadratic, Quadratic);

		virtual void destroy();

	protected:
		//
		void _initPointLight();
		void _initAreaLight();
		void _initDirectionLight();

	protected:
		//
		LightType _lightType;
		//
		Vector3 _lightSource;    //position of light source
		Vector3 _lightDir;
		
		//
		float _ambient;
		float _diffuse;
		float _spec;
		
		//
		float _constant;
		float _linear;
		float _quadratic;

	};
}

#endif