#include "UcGame.h"
#include "UcRenderMgr.h"
#include "UcShaderMgr.h"
#include "TestScene.h"
NS_UNICORN;

Game* Game::_instance = NULL;

Game::Game():
_currentWnd(0),
_runningState(RS_NORMAL)
{

}

Game* Game::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new Game;
		if (!_instance)
		{
			UCSafeDelete(_instance);
			return NULL;
		}
	}
	return _instance;
}

Game::~Game()
{
	UCSafeDelete(_instance);
}

bool Game::onAppLaunched()
{
	//launch window via glfw 
	//and event responding func
	GLViewport* viewPort = GLViewport::getInstance();
	_currentWnd = viewPort;
	_currentWnd->initialize("Unicorn Engine", 800, 600);
	GLEvent::setViewport(_currentWnd);	
	//
	_renderMgr = RenderMgr::getInstance();	
	_shaderMgr = ShaderMgr::getInstance();

	//entry to scene
	_renderMgr->initialize(viewPort,new TestScene());
	_shaderMgr->initialize();

	return true;
}

bool Game::onAppFinished()
{
	//clear ops
	glfwTerminate();
	return true;
}

int Game::run()
{
	if (!onAppLaunched())
	{
		//report error
		return RS_ERROR;
	}
	//main loop

	while (!_currentWnd->shouldBeClosed())
	{
		_renderMgr->drawScene();
	}

	if (onAppFinished())
	{

	}
	//app has exited
	return RS_EXIT;
}
