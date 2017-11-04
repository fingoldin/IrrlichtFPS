#include "stdafx.h"

#include "RunningState.h"

#include "RestingState.h"
#include "CrouchWalkingState.h"
#include "WalkingState.h"

#include "Constants.h"

void RunningState::update(Character * player, Core * core, irr::u32 time)
{
	if (lastUpdateTime == 0)
		lastUpdateTime = time;

	irr::u32 dt = time - lastUpdateTime;
	lastUpdateTime = time;

	int y = (int)player->getInputState(EIS_FORWARD) - (int)player->getInputState(EIS_BACKWARD);
	int x = (int)player->getInputState(EIS_RIGHT) - (int)player->getInputState(EIS_LEFT);

	if (y == 0 && x == 0)
		player->setState(DBG_NEW RestingState(), time);

	else if (player->getInputState(EIS_CROUCH))
		player->setState(DBG_NEW CrouchWalkingState(), time);

	else if (player->getInputState(EIS_WALK))
		player->setState(DBG_NEW WalkingState(), time);

	else
	{
		move(player, x, y, PLAYER_RUN_SPEED, dt);

		CanJumpState::update(player, core, time);
	}
}