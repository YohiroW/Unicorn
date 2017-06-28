#include "TestScene.h"
#include "SampleParticle.h"

TestScene::TestScene() :
_offSetX(0),
_offSetY(0),
_preX(0),
_preY(0),
_isDraging(false)
{

}

bool TestScene::onSceneInitialized()
{
	//-1- create a  main camera	
	Camera* cam = this->createCamera(Vector3(0.0f, 1.0f, 5.0f), FREELOOK);
	cam->setLocker(true);
	this->setCamera(cam);

	//-2- TODO: just set light position, for other attribs will not be used 
	Vector3 lightPos(5,5,5);

	//-3- create skybox then attach to current scene 
	Skybox* mSkybox = this->createSkybox("res/texture/right.png",
										"res/texture/left.png",
										"res/texture/top.png",
										"res/texture/bottom.png",
										"res/texture/back.png",
										"res/texture/front.png");
	this->setSkybox(mSkybox);

	//-4- create a entity(object in scene, which can be operated)
	//then attach a renderable object(can be shown in viewport)
	_entity = this->createEntity("Model");
	Model* model = this->createModel("res/model/jeep.obj");
	model->setLightPosition(lightPos);
	model->scale(Vector3(0.005f, 0.005f, 0.005f));
	_entity->attachRenderable(model);

	//_test = this->createEntity("Text");
	//_test->attachRenderable(new Text("TEST FONT."));

	return true;
}

void TestScene::onMouseMove(double x, double y)
{
	//-5- to view around the model
	if (!_isDraging)
	{
		_preX = x;
		_preY = y;

		return;
	}

	_offSetX = x - _preX;
	_offSetY = _preY - y;

	_entity->rotate(_offSetX* 0.2f, Vector3::AXIS_Y);
	_entity->rotate(_offSetY* 0.2f, Vector3::AXIS_X);

	_preX = x; 
	_preY = y;
}

void TestScene::onKeyPress(int keyCode, int scanCode, int mode)
{
	if (keyCode == KeyCode::KEY_1)
	{
		RenderMgr::getInstance()->replaceScene(new SampleParticle);
	}
}

void TestScene::onSceneExit()
{
	_entity->destroy();
}

void TestScene::update(float dt)
{
	//-6- judge is draging or not
	int mouseButtonState = GLEvent::getMouseState(MouseButton::LEFT_BUTTON);
	if (mouseButtonState == MouseAction::MOUSE_PRESS){
		_isDraging = true;
	}
	else if (mouseButtonState == MouseAction::MOUSE_RELEASE){
		_isDraging = false;
	}

}