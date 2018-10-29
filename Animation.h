#pragma once

#include "stdafx.h"

class Animation : public irr::scene::ISceneNodeAnimator
{
public:
	Animation() : irr::scene::ISceneNodeAnimator()
	{
		setFirstUpdate(0);
	}

	virtual ~Animation() { }
	
	virtual bool isEventReceiverEnabled() { return false; }
	virtual bool hasFinished() { return finished; }

	void setFirstUpdate(irr::u32 time) { firstUpdate = true; finished = false; startTime = time; }

protected:

	irr::u32 startTime;

	bool firstUpdate;
	bool finished;
};