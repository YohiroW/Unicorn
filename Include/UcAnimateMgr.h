#ifndef _UC_ANIMATE_MGR_H_
#define _UC_ANIMATE_MGR_H_
//
#include <gl/glew.h>
#include "UcObject.h"
#include "UcTweener.h"

namespace Unicorn
{
	class AnimateMgr: public Object
	{
	public:
		//
		static AnimateMgr* getInstance();
		//
		TransformPositionTweener* createPositionTweener(Entity* entity);
		TransformRotationTweener* createRotationTweener(Entity* entity);
		TransformScaleTweener* createScaleTweener(Entity* entity);


	private:
		static AnimateMgr* _ins;

		std::list<Tweener*> _tweenerList;
	};
}


#endif 