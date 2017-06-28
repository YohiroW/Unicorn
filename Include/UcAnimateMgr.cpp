#include "UcAnimateMgr.h"
NS_UNICORN;

AnimateMgr* AnimateMgr::_ins = NULL;

AnimateMgr* AnimateMgr::getInstance()
{
	if (!_ins)
	{
		_ins = new AnimateMgr;
		if (!_ins)
		{
			UCSafeDelete(_ins);
			return NULL;
		}
	}
	return _ins;
}

TransformPositionTweener* AnimateMgr::createPositionTweener(Entity* entity)
{
	TransformPositionTweener* postwr = new TransformPositionTweener;
	if (postwr && postwr->initialize(entity))
	{
		_tweenerList.push_back(postwr);
		return postwr;
	}
	else
	{
		UCSafeDelete(postwr);
		return NULL;
	}
}

TransformRotationTweener* AnimateMgr::createRotationTweener(Entity* entity)
{
	TransformRotationTweener* rottwr = new TransformRotationTweener;
	if (rottwr && rottwr->initialize(entity))
	{
		_tweenerList.push_back(rottwr);
		return rottwr;
	}
	else
	{
		UCSafeDelete(rottwr);
		return NULL;
	}
}

TransformScaleTweener* AnimateMgr::createScaleTweener(Entity* entity)
{
	TransformScaleTweener* scatwr = new TransformScaleTweener;
	if (scatwr && scatwr->initialize(entity))
	{
		_tweenerList.push_back(scatwr);
		return scatwr;
	}
	else
	{
		UCSafeDelete(scatwr);
		return NULL;
	}
}
