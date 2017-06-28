#pragma once
#include "Unicorn.h"

class TestScene : public Scene
{
public:
	TestScene();
	//
	virtual bool onSceneInitialized();
	virtual void onMouseMove(double x, double y);
	virtual void onKeyPress(int keyCode, int scanCode, int mode);
	virtual void onSceneExit();
	virtual void update(float dt);

private:
	//
	Entity* _entity;

	Entity* _test;
	//
	float _preX, _preY;
	float _offSetX, _offSetY;
	//
	bool _isDraging;
};

