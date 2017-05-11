#pragma once

#include "Animation.h"

class SemiAutoAnimation : public Animation
{
public:

	SemiAutoAnimation(irr::u32 time) : Animation()
	{
		shotTime = time;
	}

	virtual void animateNode(irr::scene::ISceneNode * node, irr::u32 timeMs)
	{
		if (firstUpdate)
		{
			startTime = timeMs;
			firstUpdate = false;
			node->setRotation(irr::core::vector3df(0.0f, 0.0f, 0.0f));
		}

		if ((timeMs - startTime) >= shotTime)
			finished = true;
		else
			node->setPosition(irr::core::vector3df(-0.2f - 0.2f * sin(M_PI * (double)(timeMs - startTime) / (double)shotTime), 0.4f, -0.4f));
	}

	virtual ISceneNodeAnimator * createClone(irr::scene::ISceneNode *node, irr::scene::ISceneManager *newManager = 0)
	{
		return new SemiAutoAnimation(shotTime);
	}

private:

	irr::u32 shotTime;
	irr::u32 startTime;
};