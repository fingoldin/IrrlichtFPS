#pragma once

#include "Animation.h"

class ReloadAnimation : public Animation
{
public:

	ReloadAnimation(irr::u32 time) : Animation()
	{
		runTime = time;
	}

	virtual void animateNode(irr::scene::ISceneNode * node, irr::u32 timeMs)
	{
		if (firstUpdate)
		{
			firstUpdate = false;
		}

		if (!startTime)
			startTime = timeMs;

		if (timeMs - startTime >= runTime)
			finished = true;
		else
		{
			node->setRotation(irr::core::vector3df(0.0f, -30.0f * (irr::f32)sin(M_PI * (double)(timeMs - startTime) / (double)runTime), 0.0f));
			node->setPosition(irr::core::vector3df(-0.2f, 0.4f - 0.4f * (irr::f32)sin(M_PI * (double)(timeMs - startTime) / (double)runTime), -0.4f));
		}
	}

	virtual ISceneNodeAnimator * createClone(irr::scene::ISceneNode *node, irr::scene::ISceneManager *newManager = 0)
	{
		return new ReloadAnimation(runTime);
	}

private:

	irr::u32 runTime;
};