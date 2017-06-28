#ifndef _UC_TWEENER_H_
#define _UC_TWEENER_H_
//
//#include "UcColor.h"
#include "UcAnimateCtrl.h"
#include "UcEntity.h"

namespace Unicorn
{
	//------abstract base class------
	class Tweener: public Object
	{
	public:
		static float DEFAULT_DURATION;
		static MotionFormFunc DEFAULT_MOTION_FUNC;

	public:
		Tweener(Entity* entity = NULL);
		~Tweener();

		virtual bool initialize(Entity* entity);

		inline MotionCtrler* getController()
		{
			return _ctrler;
		}

	protected:
		//abstract interface
		virtual void onUpdate() = 0;

		virtual void onEnable();
		virtual void onDisable();
		virtual void onFinished();

		virtual void destroy();

	protected:
		//
		bool _destroyOnFinish;
		//
		MotionCtrler* _ctrler;
		Entity* _entity;
		Transform _transform;
	};
	//end

	//------driven------
	class Vec3Tweener : public Tweener
	{
	public:
		//
		GEN_SGET_FUNC(Vector3, _currentValue, CurrentValue);
		GEN_SGET_FUNC(Vector3, _originValue, OrighinValue);
		GEN_SGET_FUNC(Vector3, _finalValue, FinishValue);

	protected:
		Vector3 _originValue;

		Vector3 _finalValue;

		Vector3 _currentValue;

		virtual void onUpdate()
		{
			_currentValue = (_finalValue - _originValue) * _ctrler->getCurrentValue() + _originValue;
		}
	};

	class TransformPositionTweener : public Vec3Tweener
	{
	protected:
		virtual void onUpdate()
		{
			Tweener::onUpdate();
			_transform.translate(_currentValue);
		}
	};

	//operators need to be overloaded
	//class RenderTweener : public Vec3Tweener
	//{
	//protected:
	//	ColorFRGBA _originValue;

	//	ColorFRGBA _finalValue;

	//	ColorFRGBA _currentValue;

	//protected:
	//	virtual void onUpdate()
	//	{
	//		_currentValue = (_finalValue - _originValue) * _ctrler->getCurrentValue() + _originValue;
	//	}
	//};

	class TransformRotationTweener : public Vec3Tweener
	{
	protected:
		virtual void onUpdate()
		{
			Tweener::onUpdate();
			_transform.rotateWithEuler(_currentValue);
		}
	};

	class TransformScaleTweener : public Vec3Tweener
	{
	protected:
		virtual void onUpdate()
		{
			Tweener::onUpdate();
			_transform.scale(_currentValue);
		}
	};

}



#endif