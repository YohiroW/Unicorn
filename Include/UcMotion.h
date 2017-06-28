#ifndef _UC_MOTION_H_
#define _UC_MOTION_H_
//
#include "UcEntity.h"
#include "UcAnimateMgr.h"
#include "UcVector3.h"
#include "UcAnimateCtrl.h"
//
namespace Unicorn
{
	class Motion
	{
	public:

		static Tweener* moveTo(Entity* entity, const Vector3& position)
		{
			return moveTo(entity, position, 1.0f, MotionForm::linear);
		}

		static Tweener* moveTo(Entity* entity, Vector3 position, float duration, MotionFormFunc motionFunc)
		{
			TransformPositionTweener* tweener = AnimateMgr::getInstance()->createPositionTweener(entity);

			tweener->setOrighinValue(entity->getPosition());
			tweener->setFinishValue(position);

			MotionCtrler* ctrler = tweener->getController();
			
			ctrler->setDuration(duration);
			ctrler->setMotionFunc(motionFunc);
			ctrler->play();

			return tweener;
		}




	};
}

#endif