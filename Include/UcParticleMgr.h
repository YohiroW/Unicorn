#ifndef _UC_PARTICLEMGR_H_
#define _UC_PARTICLEMGR_H_
//
#include <gl/glew.h>
#include "UcObject.h"
#include "UcParticles.h"
#include "UcVector3.h"

namespace Unicorn
{
	class ParticleMgr : public Object
	{
	public:
		~ParticleMgr();
		//
		static ParticleMgr* getInstance();
		//
		Particles* createParticle(const std::string& texture,const Vector3& pos = Vector3::ZERO);
		Particles* createParticle(Texture* texture, const Vector3& pos = Vector3::ZERO);

		virtual void destroy();

	private:
		ParticleMgr();

	private:
		static ParticleMgr* _instance;
		std::list<Particles*> _particleList;
	};
}


#endif