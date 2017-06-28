#ifndef UC_RENDERMGR_H
#define UC_RENDERMGR_H
//
#include <stack>
#include <queue>
#include "UcTextureMgr.h"
#include "UcViewport.h"
#include "UcColor.h"
#include "UcObject.h"
#include "UcCamera.h"
#include "UcScene.h"

namespace Unicorn
{
	class Mesh;
	class Game;
	class Model;
	class Renderer;
	class EventDispatcher;
	class RenderableObject;

	//
	enum RenderableType
	{
		RT_CUBE,			//these kinds of object can be renderer by
		RT_SPHERE,			//data provided within unicorn engine
		RT_PANEL,			
		RT_CYLINDER			
	};

	class RenderMgr: public Object
	{
	public:
		RenderMgr();
		~RenderMgr();
		//
		static RenderMgr* getInstance();
		static double DELTA_TIME;
		//
		bool initialize(GLViewport* view, Scene* scene);
		virtual void destroy();
		//invoked every frame
		void drawScene();
		//
		RenderableObject* createRenderableWithType(RenderableType type);
		//
		void pushScene(Scene* scene);
		Scene* popScene();
		void replaceScene(Scene* scene);
		//
		Scene* getCurrentRenderScene();
		//
		void setClearColor(ColorFRGBA color);
		//
		UCInline float getFPS() const;
		float getDeltaTime() const;
			
	protected:
		//
		float _calculateFPS(float dt) const;
		//these will be invoked by createRenderableW ithType() Func
		RenderableObject* _createCube();
		RenderableObject* _createPanel();
		RenderableObject* _createSphere();
		RenderableObject* _createCylinder();
		//
		void _renderScene(Scene* scene);

	private:
		//
		static RenderMgr* _instance;
		//draw scene and get renderable from scene
		std::stack<Scene*> _sceneStack;
		//
		EventDispatcher* _eventDispatcher;
		//after invoke drawcall this frame
		GLViewport* _view;
		GLFWwindow* _wnd;
		//
		Scene* _currenScene;
		//
		ColorFRGBA _clearColor;
		//get delta time 
		float _currentFrame;
		float _deltaTime;
		float _lastFrame;
		//
		float _framePerSec;
		//-----------------------------------
		//render datas required in current scene
		Camera* _sceneCam;
		EntityMap _entityInScene;
	};


}
#endif

