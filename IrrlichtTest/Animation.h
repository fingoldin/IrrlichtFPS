#pragma once

#include "stdafx.h"

class Animation : public irr::scene::ISceneNodeAnimator
{
public:
	Animation() : irr::scene::ISceneNodeAnimator()
	{
		setFirstUpdate();
	}

	virtual ~Animation() { }
	
	virtual bool isEventReceiverEnabled() { return false; }
	virtual bool hasFinished() { return finished; }

	void setFirstUpdate() { firstUpdate = true; finished = false; }

protected:

	bool firstUpdate;
	bool finished;
};