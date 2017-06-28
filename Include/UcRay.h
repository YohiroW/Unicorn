#ifndef _UC_RAY_H_
#define _UC_RAY_H_
//
#include "UcEntity.h"
#include "UcVector3.h"
#include "UcVector2.h"

namespace Unicorn
{
	//This ray refer to abstract ray(line) rather
	//than the ray in render system, to the latter 
	//see details in Light.
	class Ray
	{
	public:
		Ray(Vector3 src, Vector3 dst);
		~Ray();
		//
		void cast(const Vector3& src, const Vector3& dst);
		void cast(const Vector2& src, const Vector2& dst);
		
		//to see if the ray hit on entities in the scene
		bool isHitted(const Vector3& src, const Vector3& dst);
		bool isHitted(const Vector2& src, const Vector2& dst);

		//get the first entity hitted in game scene
		Entity* getHitted();
	
	private:
		bool _find();


	private:
		Vector3 _src, _dst;
	};
}

#endif