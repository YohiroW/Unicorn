#pragma once
#include "Unicorn.h"

#define ROW 3
#define COLUMN 3

class SampleBillboard : public Scene
{
public:
	//
	virtual bool onSceneInitialized();

private:
	Entity* _testEntity[12];
	Entity* _plane;
};


bool SampleBillboard::onSceneInitialized()
{
	Camera* cam = this->createCamera(Vector3(0, 4, 5), FREELOOK);
	this->setCamera(cam);

	_plane = this->createEntity("Test_Plane");
	Cube* floor = this->createCube();
	floor->attachTexture("res/texture/wood.png");
	_plane->attachRenderable(floor);
	_plane->setScale(Vector3(25.0f, 0.1f, 25.0f));


	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COLUMN; ++j)
		{
			int index = i* COLUMN + j;
			_testEntity[index] = this->createEntity("Test_Billboard_" + index);
			Billboard* billboard = this->createBillboard("res/texture/tree.png", Vector3(-1.0f + i, 2,  0.5f* j));
			_testEntity[index]->attachRenderable(billboard);
		}
	}

	return true;
}

