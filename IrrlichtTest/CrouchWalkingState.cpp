#include "stdafx.h"

#include "CrouchWalkingState.h"

#include "RunningState.h"
#include "CrouchRestingState.h"
#include "WalkingState.h"

#include "Constants.h"

void CrouchWalkingState::update(Character * player, Core * core, irr::u32 time)
{
	if (lastUpdateTime == 0)
		lastUpdateTime = time;

	irr::u32 dt = time - lastUpdateTime;
	lastUpdateTime = time;

	if (!player || !core)
		return;

	int y = (int)player->getInputState(EIS_FORWARD) - (int)player->getInputState(EIS_BACKWARD);
	int x = (int)player->getInputState(EIS_RIGHT) - (int)player->getInputState(EIS_LEFT);

	if (y == 0 && x == 0)
		player->setState(DBG_NEW CrouchRestingState(), time);

	else if (!player->getInputState(EIS_CROUCH))
	{
		if (player->getInputState(EIS_WALK))
			player->setState(DBG_NEW WalkingState(), time);
		else
			player->setState(DBG_NEW RunningState(), time);
	}

	else
	{
		move(player, x, y, PLAYER_CROUCH_SPEED, dt);

		CrouchingState::update(player, core, time);
	}
}