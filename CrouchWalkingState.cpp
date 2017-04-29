#include "stdafx.h"

#include "CrouchWalkingState.h"

#include "RunningState.h"
#include "CrouchRestingState.h"
#include "WalkingState.h"

void CrouchWalkingState::update(Character * player, Core * core, irr::u32 dt)
{
	int y = (int)player->getInputState(EIS_FORWARD) - (int)player->getInputState(EIS_BACKWARD);
	int x = (int)player->getInputState(EIS_RIGHT) - (int)player->getInputState(EIS_LEFT);

	if (y == 0 && x == 0)
		player->setState(DBG_NEW CrouchRestingState());

	else if (!player->getInputState(EIS_CROUCH))
	{
		if (player->getInputState(EIS_WALK))
			player->setState(DBG_NEW WalkingState());
		else
			player->setState(DBG_NEW RunningState());
	}

	PlayerState::update(player, core, dt);
}