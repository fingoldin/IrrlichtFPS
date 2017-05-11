#pragma once

#include "Animation.h"

class RestAnimation : public Animation
{
public:

	RestAnimation() : Animation()
	{
	}

	virtual void animateNode(irr::scene::ISceneNode * node, irr::u32 timeMs)
	{
		if (firstUpdate)
		{
			startTime = timeMs;
			firstUpdate = false;
			node->setRotation(irr::core::vector3df(0.0f, 0.0f, 0.0f));
		}

		node->setPosition(irr::core::vector3df(-0.2f, 0.4f + 0.03f * sin(0.01 * (double)(timeMs - startTime)), -0.4f));
	}

	virtual ISceneNodeAnimator * createClone(irr::scene::ISceneNode *node, irr::scene::ISceneManager *newManager = 0)
	{
		return new RestAnimation();
	}

private:

	irr::u32 startTime;
};