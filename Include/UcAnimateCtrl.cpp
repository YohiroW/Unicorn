#include "UcAnimateCtrl.h"
#include "UcRenderMgr.h"

//
NS_UNICORN;

MotionCtrler::MotionCtrler() :
_currentTime(0),
_currentOffset(0),
_currentValue(0),
_originValue(0),
_finalValue(0),
_duration(1.0f),
_loopCount(0),
_loopTimes(1),
_currentState(STOP),
_preState(STOP),
_updateType(NORMAL),
_loopType(REPEAT),
_finishState(CONSTANT),
_motionFormFunc(MotionForm::linear)
{
}

MotionCtrler::~MotionCtrler()
{

}

void MotionCtrler::onMotionUpdate()
{
	this->_updateFunc();
}

void MotionCtrler::onMotionStateChanged()
{

}

void MotionCtrler::onMotionLooping()
{

}

void MotionCtrler::onMotionFinish()
{

}

void MotionCtrler::onEnable()
{
	this->resume();
}

void MotionCtrler::onDisable()
{
	this->pause();
}

bool MotionCtrler::isMotionPlaying()
{
	return _currentState == PLAYING || _currentState == REVERSE;
}

void MotionCtrler::resume()
{
}

void MotionCtrler::play()
{
	this->setMotionState(MotionState::PLAYING);
}

void MotionCtrler::pause()
{
	this->setMotionState(MotionState::PAUSE);
}

void MotionCtrler::reverse()
{
	this->setMotionState(MotionState::REVERSE);
}

void MotionCtrler::stop()
{
	this->setMotionState(MotionState::STOP);
	
	//clean loop counter
	_loopCount = 0;
	
	if (_finishState == MotionFinishState::RESET)
	{
		skipToBegin();
	}
	//Stop thread "ticker"
}

void MotionCtrler::skipTo(const float& time)
{
	_currentTime = Math::clamp(time / _duration, 0, 1);
	float targetValue = (_finalValue - _originValue) * _currentTime + _originValue;
	_currentOffset = targetValue - _currentValue;
	_currentValue = targetValue;

	this->onMotionUpdate();
}

void MotionCtrler::skipToBegin()
{
	this->skipTo(0);
}

void MotionCtrler::skipToEnd()
{
	this->skipTo(_duration);
}

MotionState MotionCtrler::getCurrentState() const
{
	return this->_currentState;
}

MotionState MotionCtrler::getPreState() const
{
	return this->_preState;
}

void MotionCtrler::setMotionState(const MotionState& targetState)
{
	if (targetState == _currentState)
	{
		return;
	}
	_preState = _currentState;
	_currentState = targetState;
	
	this->onMotionStateChanged();

	//stop thread "ticker"
	if (this->isMotionPlaying())
	{
		//begin thread "ticker"
	}
}

void MotionCtrler::_tick(const float& time)
{
	bool isFinished = false;

	if (_currentState == MotionState::PLAYING)
	{
		_currentTime = Math::clamp(_currentTime + time / _duration, 0, 1);
		isFinished = Math::approximate(_currentTime, 1.0f);
	}
	else
	{
		_currentTime = Math::clamp01(_currentTime - time / _duration);
		isFinished = Math::approximate(_currentTime, 0.0f);
	}

	//
	float frameValue = (_finalValue - _originValue) * _motionFormFunc(0.0f, 1.0f, _currentTime) + _originValue;
	_currentOffset = frameValue - _currentValue;
	_currentValue = frameValue;
	
	//if (eventUpdate != null)
	//{
	//	//dispatch msg to delegate pointed
	//	eventUpdate(this, EventArgs.Empty);
	//}
	this->onMotionUpdate();
	 
	if (isFinished)
	{
		_loopCount++;

		if (_loopTimes < 0 || _loopCount <= _loopTimes)
		{
			if (_loopType == MotionLoopType::REPEAT)
			{
				skipToBegin();
			}
			else
			{
				this->setMotionState(_currentState == MotionState::PLAYING ?
									 MotionState::REVERSE : 
									 MotionState::PLAYING);
			}

		/*	if (eventLooping != null)
			{
				eventLooping(this, EventArgs.Empty);
			}*/
			
			this->onMotionLooping();
		}
		else
		{
	/*		if (eventFinished != null)
			{
				eventFinished(this, EventArgs.Empty);
			}*/
			
			this->onMotionFinish();
			
			this->stop();
		}
	}
}

void MotionCtrler::_ticker()
{
	while (true)
	{
		float dt = RenderMgr::getInstance()->getDeltaTime();
		switch (_updateType)
		{
		case NORMAL:
			//update every frame
			this->_tick(dt);
			break;
		case PHYSICS:
			//this should update every time with physics engine
			this->_tick(dt);
			break;
		case REALTIME:
		
			break;
		}
	}
}

void MotionCtrler::_setPreMotionState(const MotionState& targetState)
{
	_preState = targetState;
}

void MotionCtrler::setUpdateFunc(MotionUpdateFunc func)
{
	//??
}

void MotionCtrler::setMotionFunc(MotionFormFunc func)
{
	//
	_motionFormFunc = func;
}

