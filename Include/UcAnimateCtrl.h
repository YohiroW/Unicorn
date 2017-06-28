#ifndef _UC_ANIMECTRL_H_
#define _UC_ANIMECTRL_H_
//
#include <gl/glew.h>
#include <functional>
#include "UcObject.h"
#include "UcMotionForms.h"

namespace Unicorn
{
	typedef std::function< float(float, float, float)>  MotionFormFunc;
	typedef std::function< void(void)> MotionUpdateFunc;

	enum MotionUpdateType
	{
		NORMAL,
		PHYSICS,
		REALTIME
	};

	enum MotionState
	{
		STOP,
		PAUSE,
		PLAYING,
		REVERSE
	};

	enum MotionFinishState
	{
		RESET,
		CONSTANT
	};

	enum MotionLoopType
	{
		REPEAT,
		PINGPONG		//just like swing, you know = =|||
	};
 

	class MotionCtrler: public Object
	{
	public:
		MotionCtrler();
		~MotionCtrler();
		
		//
		virtual void onMotionUpdate();
		virtual void onMotionStateChanged();
		virtual void onMotionLooping();
		virtual void onMotionFinish();

		//
		virtual void onEnable();
		virtual void onDisable();

		//
		bool isMotionPlaying();
		void resume();
		void play();
		void pause();
		void reverse();
		void stop();

		//
		void skipTo(const float& time);
		void skipToBegin();
		void skipToEnd();

		//
		GEN_SGET_FUNC(float, _currentTime, CurrenTime);
		GEN_SGET_FUNC(float, _currentValue, CurrentValue);
		GEN_SGET_FUNC(float, _currentOffset, CurrenOffset);
		GEN_SGET_FUNC(int, _loopCount, CurrentLoopCount);
		GEN_SGET_FUNC(float, _duration, Duration);

		//
		void setMotionState(const MotionState& targetState);
		MotionState getCurrentState() const;
		MotionState getPreState() const;

		void setUpdateFunc(MotionUpdateFunc func);
		void setMotionFunc(MotionFormFunc func);


	protected:
		//
		void _tick(const float& time);
		void _ticker();
		//
		void _setPreMotionState(const MotionState& targetState);

	private:
		//
		float _currentTime;
		float _currentValue;
		float _currentOffset;
		
		//
		float _originValue;
		float _finalValue;
		float _duration;
		int _loopCount;
		int _loopTimes;

		//
		MotionState _currentState;
		MotionState _preState;
		MotionUpdateType _updateType;
		MotionLoopType _loopType;
		MotionFinishState _finishState;

		//the motion form which you want to show
		MotionFormFunc _motionFormFunc;
		MotionUpdateFunc _updateFunc;

	};


}


#endif