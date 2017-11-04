#include "stdafx.h"

#include "RestingState.h"

#include "WalkingState.h"
#include "RunningState.h"

#include "CrouchRestingState.h"

void RestingState::update(Character * player, Core * core, irr::u32 time)
{
	if (lastUpdateTime == 0)
		lastUpdateTime = time;

	irr::u32 dt = time - lastUpdateTime;
	lastUpdateTime = time;

	int y = (int)player->getInputState(EIS_FORWARD) - (int)player->getInputState(EIS_BACKWARD);
	int x = (int)player->getInputState(EIS_RIGHT) - (int)player->getInputState(EIS_LEFT);

	if (y != 0 || x != 0)
	{
		if (player->getInputState(EIS_WALK))
			player->setState(DBG_NEW WalkingState(), time);
		else
			player->setState(DBG_NEW RunningState(), time);
	}
	else if (player->getInputState(EIS_CROUCH))
		player->setState(new CrouchRestingState(), time);
	else
	{
		ThirdPersonNode n = player->getThirdPersonNode();

		if (n.leftLeg && n.rightLeg)
		{
			irr::f32 angle = n.leftLeg->getRotation().X;

			if (angle > 0.1f)
				angle -= 10.0f * ((irr::f32)dt / 1000.0f);
			else if (angle < -0.1f)
				angle += 10.0f * ((irr::f32)dt / 1000.0f);
			else
				angle = 0.0f;

			n.leftLeg->setRotation(irr::core::vector3df(angle, 0.0f, 0.0f));
			n.rightLeg->setRotation(irr::core::vector3df(-angle, 0.0f, 0.0f));
		}

		StandingState::update(player, core, time);
	}
}