#pragma once
#include "Unicorn.h"
#include "SampleBillboard.h"

class SampleParticle : public Scene
{
public:
	//
	virtual bool onSceneInitialized();
	virtual void onKeyPress(int keyCode, int scanCode, int mode);

private:
	Entity* _testEntity;
};


bool SampleParticle::onSceneInitialized()
{
	Camera* cam = this->createCamera(Vector3::ZERO, FREELOOK);
	this->setCamera(cam);

	_testEntity = this->createEntity("Particle");
	Particles* particle = ParticleMgr::getInstance()->createParticle("res/texture/particle.png", Vector3(0, 0, -20));
	_testEntity->attachRenderable(particle);

	return true;
}

void SampleParticle::onKeyPress(int keyCode, int scanCode, int mode)
{
	if (keyCode == KeyCode::KEY_1)
	{
		_testEntity->destroy();

		RenderMgr::getInstance()->replaceScene(new SampleBillboard);
	}
}
