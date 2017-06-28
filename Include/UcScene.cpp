#include "UcScene.h"
#include "UcShaderMgr.h"
#include "UcRenderableObject.h"
#include "UcEventDispatcher.h"
#include "UcBillboard.h"
#include "UcConfig.h"
#include "UcLogger.h"
NS_UNICORN;

Scene::Scene() :
_isInitialized(false),
_isEnded(false),
_dispatcher(NULL),
_camera(NULL)
{
}

Scene::~Scene()
{

}

bool Scene::initialize()
{
	_dispatcher = EventDispatcher::getInstance();
	//get camera

	return true;
}

bool Scene::onSceneInitialized()
{
	_isInitialized = true;

	return true;
}

void Scene::onSceneExit()
{

}

void Scene::update(float dt)
{
}

Entity* Scene::createEntity(const std::string& name)
{
	Entity* entity = new Entity;
	if (entity->initialize(name) && entity)
	{
		//insert into entityMap with pair like name - entity
		_entityMap[name] = entity;
		return entity;
	}
	else
	{
		entity->destroy();
		entity = NULL;
		return NULL;
	}
}

bool Scene::isInitialized()
{
	if (!_isInitialized)
	{
		_isInitialized = true;
		return false;
	}
	return _isInitialized;
}

bool Scene::isEnded() const
{

	return _isEnded;
}

void Scene::dispatchEvent()
{
	_dispatcher->addListener(this);
}

void Scene::removeEntity(const std::string& name)
{
	_entityMap[name]->destroy();
}

EntityMap Scene::getEntityMap() const
{
	return _entityMap;
}

Cube* Scene::createCube()
{
	Cube* cube = new Cube;
	if (cube && cube->initialize())
	{
		//cube->setTransform();
		return cube;
	}
	else
	{
		UCSafeDelete(cube);
		return NULL;
	}
}

Plane* Scene::createPlane()
{
	Plane* plane = new Plane;
	if (plane && plane->initialize())
	{

		return plane;
	}
	else
	{
		UCSafeDelete(plane);
		return NULL;
	}
}


Skybox* Scene::createSkybox(const char* right, const char* left, const char* top, const char* bottom, const char* back, const char* front)
{
	Skybox* skybox = new Skybox;
	if (skybox && skybox->initialize(right,left,top,bottom,back,front))
	{
		return skybox;
	}
	else
	{
		UCSafeDelete(skybox);
		return NULL;
	}
}

Camera* Scene::createCamera(const Vector3& pos, CameraType type)
{
	Camera* camera = new Camera;
	if (camera && camera->initialize(pos, type))
	{
		//
		return camera;
	}
	else
	{
		UCSafeDelete(camera);
		return NULL;
	}
}

Model* Scene::createModel(const char* path)
{
	Model* model = new Model();
	if (model && model->initialize(path))
	{
		return model;
	}
	else
	{
		UCSafeDelete(model);
		return NULL;
	}
}

Billboard* Scene::createBillboard(const char* texturePath, const Vector3& pos)
{
	Billboard* billboard = new Billboard();
	if (billboard && billboard->initialize(texturePath, pos))
	{
		return billboard;
	}
	else
	{
		UCSafeDelete(billboard);
		return NULL;
	}
}

void Scene::destroy()
{
	_isEnded = true;
	
	if (_camera){
		_camera->destroy();
	}

	if (_skybox){
		_skybox->destroy();
	}
	
	//remove func from dispatcher	
	_dispatcher->removeListener(this);
	//destroy entity
	for (auto iter: _entityMap)
	{
		iter.second->destroy();
	}
	_entityMap.clear();

	delete this;
}

void Scene::setCamera(Camera* cam)
{
	if (!cam)
		return;
	//
	_camera = cam;
}

void Scene::setSkybox(Skybox* skybox)
{
	if (!skybox)
		return;
	//
	_skybox = skybox;
}

void Scene::setSceneEnd(bool isEnd)
{
	_isEnded = isEnd;
}


