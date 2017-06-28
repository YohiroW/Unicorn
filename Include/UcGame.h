//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")  

#ifndef GAME_H
#define  GAME_H
//
#include <cstdlib>
#include "UcMacros.h"
#include "UcApplication.h"
#include "UcViewport.h"
#include "UcEvent.h"

namespace Unicorn
{
	class ShaderMgr;
	class RenderMgr;

	class Game: public Application
	{
	public:
		~Game();
		//
		static Game* getInstance();
		//
		virtual bool onAppLaunched();
		virtual bool onAppFinished();
		virtual int run();
		//
		inline int getRunningState() const;
		inline double getTime() const;
		inline float getWidthHeightRatio() const;
		inline int getWidth() const;
		inline int getHeight() const;
		//
	private:
		//prevent creating from outside
		Game();



	private:
		static Game* _instance;
		GLViewport* _currentWnd;
		RunningState _runningState;

		RenderMgr* _renderMgr;
		ShaderMgr* _shaderMgr;	
	};
	#include "UcGame.inl"


}// Namespace

#endif // GAME_H
