#ifndef _UC_SCENE_H_
#define _UC_SCENE_H_
//
#include <map>
#include <vector>
#include <gl/glew.h>
#include "UcMainCamera.h"
#include "UcModel.h"
#include "UcEntity.h"
#include "UcSkybox.h"
#include "UcSmartPtr.h"
#include "UcEventNode.h"
#include "UcCube.h"
#include "UcPlane.h"

namespace Unicorn
{
	class EventDispatcher;
	class Billboard;

	typedef SmartPtr<Entity> EntityPtr;
	typedef std::map<std::string, Entity*> EntityMap;
	typedef std::vector<RenderableObject*> RenderableMap;

	class Scene : public Listener
	{		
	public:
		//
		virtual bool initialize();
		//
		virtual bool onSceneInitialized();
		virtual void onSceneExit();
		virtual void update(float dt);
		//
		Entity* createEntity(const std::string& name);
		void removeEntity(const std::string& name);
		void removeEntity(Entity* entity);
		//
		Skybox* createSkybox(const char* right = Skybox::DEFAULT_SKYBOX_RIGHT,
		                     const char* left = Skybox::DEFAULT_SKYBOX_LEFT,
			                 const char* top = Skybox::DEFAULT_SKYBOX_TOP,
			                 const char* bottom = Skybox::DEFAULT_SKYBOX_BOTTOM,
			                 const char* back = Skybox::DEFAULT_SKYBOX_BACK,
			                 const char* front = Skybox::DEFAULT_SKYBOX_FRONT);
		//
		Camera* createCamera(const Vector3& pos, CameraType type);
		Billboard* createBillboard(const char* texturePath, const Vector3& pos = Vector3::ZERO);
		Model* createModel(const char* path);
		
		//base object
		Cube* createCube();
		Plane* createPlane();
		//Sphere* createSphere();

		//
		EntityMap getEntityMap() const;
		//
		void dispatchEvent();

		inline Camera* getCamera() const;
		inline Skybox* getSkybox() const;
		
		bool isInitialized();
		//
		bool isEnded() const; 
		void setSceneEnd(bool isEnd);
		//
		virtual void destroy();
		//pass a reference into this func, this method wont return result directly
		static void findAllEntitiesByName(const std::string name, EntityMap& EntitySets);
		//easy to find a entity by name	
		static Entity* findEntityByName(const std::string name);

		
		
		virtual ~Scene();
		

	protected:
		//
		Scene();
		void setCamera(Camera* cam);
		void setSkybox(Skybox* skybox);

	protected:
		//
		Camera* _camera;
		Skybox* _skybox;


	private:
		//
		EventDispatcher* _dispatcher;
		//to store each entity created in this scene 
		EntityMap _entityMap;
		//
		bool _isInitialized, _isEnded;
	};
	#include "UcScene.inl"

}


#endif