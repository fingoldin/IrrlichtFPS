#pragma once

#include "Animation.h"

class SwitchAnimation : public Animation
{
public:

	SwitchAnimation(irr::u32 time) : Animation()
	{
		runTime = time;
	}

	virtual void animateNode(irr::scene::ISceneNode * node, irr::u32 timeMs)
	{
		if (firstUpdate)
		{
			startTime = timeMs;
			firstUpdate = false;
		}

		if (timeMs - startTime >= runTime)
			finished = true;
		else
		{
			node->setRotation(irr::core::vector3df(0.0f, 0.0f, -90.0f * sin(0.5f * M_PI - 0.5f * M_PI * (double)(timeMs - startTime) / (double)runTime)));
			node->setPosition(irr::core::vector3df(-0.2f, -1.0f + 1.4f * (double)(timeMs - startTime) / (double)runTime, -0.4f));
		}
	}

	virtual ISceneNodeAnimator * createClone(irr::scene::ISceneNode *node, irr::scene::ISceneManager *newManager = 0)
	{
		return new SwitchAnimation(runTime);
	}

private:

	irr::u32 runTime;
	irr::u32 startTime;
};