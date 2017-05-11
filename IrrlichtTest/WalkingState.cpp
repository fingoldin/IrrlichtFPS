#include "stdafx.h"

#include "WalkingState.h"

#include "RestingState.h"
#include "CrouchWalkingState.h"
#include "RunningState.h"

#include "Constants.h"

void WalkingState::update(Character * player, Core * core, irr::u32 time)
{
	if (lastUpdateTime == 0)
		lastUpdateTime = time;

	irr::u32 dt = time - lastUpdateTime;
	lastUpdateTime = time;

	int y = (int)player->getInputState(EIS_FORWARD) - (int)player->getInputState(EIS_BACKWARD);
	int x = (int)player->getInputState(EIS_RIGHT) - (int)player->getInputState(EIS_LEFT);

	if (y == 0 && x == 0)
		player->setState(DBG_NEW RestingState());

	else if (player->getInputState(EIS_CROUCH))
		player->setState(DBG_NEW CrouchWalkingState());

	else if (!player->getInputState(EIS_WALK))
		player->setState(DBG_NEW RunningState());

	else
		move(player, x, y, PLAYER_WALK_SPEED, dt);

	StandingState::update(player, core, time);
}