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
			firstUpdate = false;
			node->setPosition(irr::core::vector3df(-0.4f, 0.4f, -0.4f));
		}

		if (!startTime)
			startTime = timeMs;

		if ((timeMs - startTime) >= shotTime)
			finished = true;
		else
			node->setPosition(irr::core::vector3df(-0.2f - 0.2f * (irr::f32)sin(M_PI * 0.5f + 0.5f * M_PI * (double)(timeMs - startTime) / (double)shotTime), 0.4f, -0.4f));
	}

	virtual ISceneNodeAnimator * createClone(irr::scene::ISceneNode *node, irr::scene::ISceneManager *newManager = 0)
	{
		return new SemiAutoAnimation(shotTime);
	}

private:

	irr::u32 shotTime;
};