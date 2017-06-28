#include "UcGame.h"
#include "UcLogger.h"
#include "UcRenderMgr.h"
#include "UcShaderMgr.h"
#include "UcEventDispatcher.h"
#include "UcRenderableObject.h"
//
NS_UNICORN;
RenderMgr* RenderMgr::_instance = NULL;
double RenderMgr::DELTA_TIME = 0;

RenderMgr::RenderMgr() :
_wnd(NULL),
_view(NULL),
_sceneCam(NULL),
_deltaTime(0),
_lastFrame(0),
_framePerSec(0),
_currentFrame(0),
_clearColor(ColorFRGBA::GRAY)
{
}

RenderMgr::~RenderMgr()
{
	this->destroy();
  
}

RenderMgr* RenderMgr::getInstance()
{
	if (!_instance)
	{
		_instance = new RenderMgr;
		if (!_instance)
		{
			UCSafeDelete(_instance);
			return NULL;
		}
	}
	return _instance;
}

bool RenderMgr::initialize(GLViewport* view, Scene* scene)
{
	if (!view || !scene || !scene->initialize())
		return false;
	//
	_view = view;
	_wnd = _view->getWindow();
	//
	_currenScene = scene;
	_sceneStack.push(scene);
	//
	if (Game::getInstance()->getRunningState() != Game::RunningState::RS_PAUSE)
	{
		//dispatch event
		EventDispatcher::getInstance()->addListener(_currenScene);
	}
	TextureMgr::getInstance()->initialize();

	return true;
}

void RenderMgr::destroy()
{
	UCSafeDelete(_instance);
}

void RenderMgr::drawScene()
{
	//calculate deltaTime
	_currentFrame = glfwGetTime();
	_deltaTime = _currentFrame - _lastFrame;
	DELTA_TIME = _deltaTime;
	_lastFrame = _currentFrame;
	//
	_framePerSec = _calculateFPS(_deltaTime);

	//update event and callback func of it
	glfwPollEvents();
	//set clear color
	glClearColor(_clearColor.R, _clearColor.G, _clearColor.B, _clearColor.A);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//draw each object in render queue
	if (!_currenScene->isInitialized())
	{
		_currenScene->onSceneInitialized();
		//get camera from scene, so that we can get view and prj matrix further
		_sceneCam = _currenScene->getCamera();
		//get renderable objects from entities in scene
		_entityInScene = _currenScene->getEntityMap();
	}

	//render
	this->_renderScene(_currenScene);
	_currenScene->update(_deltaTime);

	//when scene is ended
	if (_currenScene->isEnded())
	{
		_currenScene->onSceneExit();
	}

	glfwSwapBuffers(_wnd);
}

float RenderMgr::_calculateFPS(float dt) const
{
	//
	float fps = 1.0f / 60;
	//
	if (fps > FRAME_PER_SEC)
		fps = FRAME_PER_SEC;

	return fps;
}

RenderableObject* RenderMgr::_createCube()
{
	return NULL;

}

RenderableObject* RenderMgr::_createPanel()
{
	return NULL;

}

RenderableObject* RenderMgr::_createSphere()
{
	return NULL;

}

RenderableObject* RenderMgr::_createCylinder()
{
	return NULL;
}

void RenderMgr::_renderScene(Scene* scene)
{
	if (scene == NULL)
	{
		Log("scene is nil, can not be rendered.");
		return;
	}//
	
	_sceneCam->update(_deltaTime);
	for (auto iter : _entityInScene)
	{
		iter.second->update(_deltaTime);
		RenderableObject* renderable = iter.second->getRenderable();
		if (renderable->isEnabled())
		{
			renderable->onPreRender(_sceneCam);
			renderable->draw(_deltaTime);
			renderable->onPostRender();
		}
	}//

	Skybox* skybox = scene->getSkybox();
	if (skybox)
	{
		if (skybox->isEnabled())
		{
			skybox->onPreRender(_sceneCam);
			skybox->draw(_deltaTime);
			skybox->onPostRender();
		}
	}//
}


void RenderMgr::pushScene(Scene* scene)
{
	//
	_sceneStack.push(scene);
}

Scene* RenderMgr::popScene()
{
	Scene* scene = _sceneStack.top();
	_sceneStack.pop();

	return scene;
}

void RenderMgr::replaceScene(Scene* scene)
{
	//clear and destroy old scene                                                                       
	Scene* preScene = _sceneStack.top();
	_sceneStack.pop();

	//skip to new scene
	_sceneStack.push(scene);
	_currenScene = scene;
	EventDispatcher::getInstance()->addListener(_currenScene);

	preScene->destroy();
	preScene = NULL;
}

float RenderMgr::getDeltaTime() const
{
	return _deltaTime;
}

