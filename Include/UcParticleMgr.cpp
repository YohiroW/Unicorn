#include "UcParticleMgr.h" 
NS_UNICORN;

//
ParticleMgr* ParticleMgr::_instance = NULL;

//private construction
ParticleMgr::ParticleMgr()
{
}

ParticleMgr::~ParticleMgr()
{

}

ParticleMgr* ParticleMgr::getInstance()
{
	if (!_instance)
	{
		_instance = new ParticleMgr;
		if (!_instance)
		{
			UCSafeDelete(_instance);			
			assert("The memory is out of allocating.");
			return NULL;
		}
	}
	return _instance;
}

Particles* ParticleMgr::createParticle(const std::string& texture,const Vector3& pos /* = Vector3::ZERO */)
{
	Particles* particles = new Particles();
	if (particles && particles->initialize(texture,pos))
	{
		_particleList.push_back(particles);
		return particles;
	}
	else
	{
		UCSafeDelete(particles);
		return NULL;
	}
}

Particles* ParticleMgr::createParticle(Texture* texture, const Vector3& pos /* = Vector3::ZERO */)
{
	Particles* particles = new Particles();
	if (particles && particles->initialize(texture, pos))
	{
		_particleList.push_back(particles);
		return particles;
	}
	else
	{
		UCSafeDelete(particles);
		return NULL;
	}
}

void ParticleMgr::destroy()
{
	for (auto iter : _particleList)
	{
		if (iter)
		{
			iter->destroy();
			UCSafeDelete(iter);
			_particleList.remove(iter);
		}
		else
			_particleList.remove(iter);
	}
	_particleList.clear();
}


